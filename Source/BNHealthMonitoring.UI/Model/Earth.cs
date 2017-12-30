using System.Windows.Media;
using System.Windows.Media.Media3D;
using HelixToolkit.Wpf;

namespace BNHealthMonitoring.UI.Model
{ 
    public class FlightVisual3D : ModelVisual3D
    {
        public static double EarthRadiusKm = 6371;

        public FlightVisual3D(Point3D p1)
        {
            var tube = new TubeVisual3D();
            tube.Fill = new SolidColorBrush(Color.FromArgb(80, 255, 255, 255));
            Children.Add(tube);
            Children.Add(new SphereVisual3D() { Center = p1, Radius = 100, Material = Materials.Red });
        }
    }
}