namespace Monitor.ViewApp.View
{
    using System;
    using System.Reactive.Linq;
    using System.Threading.Tasks;
    using System.Windows;
    using System.Windows.Controls;
    using System.Windows.Input;
    using System.Windows.Media.Media3D;

    using HelixToolkit.Wpf;

    using Monitor.ViewApp.BL;

    public partial class EarthView : UserControl
    {
        private DataState m_dataState;
        private const int EARTH_RADIUS = 6371;
        private static EarthView s_view = null;

        public static EarthView GetInstance()
        {
            if (s_view == null)
                s_view = new EarthView();

            return s_view;
        }

        private EarthView()
        {
            InitializeComponent();
            EarthModule.Radius = EARTH_RADIUS;
            Loaded += userControlLoaded;
            m_dataState = DataState.GetInstance();
            m_dataState.LocationUpdated.ObserveOnDispatcher().Subscribe(onLocationUpdate);
            DataContext = this;
        }

        private async void onLocationUpdate(Point3D p_point)
        {
            await addPoint(p_point);
        }

        private async Task addPoint(Point3D p_point)
        {
            EarthViewport.Children.Add(new SphereVisual3D() { Center = p_point, Radius = 80, Material = Materials.Green });

            if (EarthViewport.Children.Count > 3)
            {
                SphereVisual3D sv = EarthViewport.Children[EarthViewport.Children.Count - 2] as SphereVisual3D;

                if (sv == null)
                    return;

                sv.Material = Materials.Red;
            }
        }

        private void userControlLoaded(object p_sender, RoutedEventArgs p_e)
        {
            EarthViewport.ZoomExtents();
            EarthViewport.IsPanEnabled = false;
            EarthViewport.IsTouchZoomEnabled = false;

            EarthViewport.ZoomGesture2 = new MouseGesture()
            {
                MouseAction = MouseAction.LeftClick,
                Modifiers = ModifierKeys.None
            };
        }

    }
}