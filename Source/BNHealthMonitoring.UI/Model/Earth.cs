using System.Windows.Media;
using System.Windows.Media.Media3D;
using HelixToolkit.Wpf;

namespace BNHealthMonitoring.UI.Model
{
    public class GeocentricPointVisual3D : ModelVisual3D
    {
        public static double EarthRadiusKm = 6371;

        public GeocentricPointVisual3D(Point3D p_point)
        {
            Children.Add(new SphereVisual3D() { Center = p_point, Radius = 80, Material = Materials.Red });
        }
    }
}