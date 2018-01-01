using System;
using System.Reactive.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Media3D;
using BNHealthMonitoring.UI.BL;
using HelixToolkit.Wpf;

namespace BNHealthMonitoring.UI.View
{
    public partial class EarthView : UserControl
    {
        private DataState m_dataState;
        private const int EARTH_RADIUS = 6371;

        public EarthView()
        {
            InitializeComponent();
            EarthModule.Radius = EARTH_RADIUS;
            CloudsLayer.Radius = EarthModule.Radius + 350;
            Loaded += userControlLoaded;
            m_dataState = DataState.GetInstance();
            m_dataState.LocationUpdated.ObserveOnDispatcher().Subscribe(onLocationUpdate);
            this.Clouds = MaterialHelper.CreateImageMaterial("pack://application:,,,/Resources/clouds.jpg", 0.5);
            DataContext = this;
        }

        public static readonly DependencyProperty CloudsProperty = DependencyProperty.Register(
                "Clouds", typeof(Material), typeof(MainWindow), new UIPropertyMetadata(null));


        public Material Clouds
        {
            get
            {
                return (Material)this.GetValue(CloudsProperty);
            }

            set
            {
                this.SetValue(CloudsProperty, value);
            }
        }

        private async void onLocationUpdate(Point3D p_point)
        {
            await addPoint(p_point);
        }

        private async Task addPoint(Point3D p_point)
        {
            EarthViewport.Children.Add(new SphereVisual3D() { Center = p_point, Radius = 80, Material = Materials.Red });
        }

        private void userControlLoaded(object p_sender, RoutedEventArgs p_e)
        {
            EarthViewport.ZoomExtents();
           // EarthViewport.IsZoomEnabled = false;
            EarthViewport.IsPanEnabled = false;
            EarthViewport.IsTouchZoomEnabled = false;
        }

    }
}