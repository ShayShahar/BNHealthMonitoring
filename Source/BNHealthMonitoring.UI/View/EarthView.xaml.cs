using System;
using System.Reactive.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Media3D;
using BNHealthMonitoring.UI.BL;
using BNHealthMonitoring.UI.Model;

namespace BNHealthMonitoring.UI.View
{
    public partial class EarthView : UserControl
    {
        private DataState m_dataState;
        public EarthView()
        {
            InitializeComponent();
            EarthModule.Radius = GeocentricPointVisual3D.EarthRadiusKm;
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
            EarthViewport.Children.Add(new GeocentricPointVisual3D(p_point));
        }

        private void userControlLoaded(object p_sender, RoutedEventArgs p_e)
        {
            EarthViewport.ZoomExtents();
            EarthViewport.IsZoomEnabled = false;
            EarthViewport.IsPanEnabled = false;
            EarthViewport.IsTouchZoomEnabled = false;

            //var ftv = new FlightVisual3D(new Point3D(7071.022, 0, -0.00126));
            //EarthViewport.Children.Add(ftv);
            //ftv = new FlightVisual3D(new Point3D(7064.63706, 188.3284, 236.76));
            //EarthViewport.Children.Add(ftv);
            //ftv = new FlightVisual3D(new Point3D(7069.42557, 94.18549, 118.40619));
            //EarthViewport.Children.Add(ftv);
            //ftv = new FlightVisual3D(new Point3D(7056.65872, 282.38623, 355.00661));
            //EarthViewport.Children.Add(ftv);
            //ftv = new FlightVisual3D(new Point3D(7045.49436,  376.31651,   473.09249));
            //EarthViewport.Children.Add(ftv);
            //ftv = new FlightVisual3D(new Point3D(7031.14927, 470.07686,   590.9642));
            //EarthViewport.Children.Add(ftv);
            //ftv = new FlightVisual3D(new Point3D(7013.63026,    563.62495,   708.56843));
            //EarthViewport.Children.Add(ftv);
            //ftv = new FlightVisual3D(new Point3D(6992.94563, 656.91861,   825.85199));
            //EarthViewport.Children.Add(ftv);
        }

    }
}