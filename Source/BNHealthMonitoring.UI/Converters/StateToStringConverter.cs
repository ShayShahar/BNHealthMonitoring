using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Data;
using BNHealthMonitoring.UI.View;

namespace BNHealthMonitoring.UI.Converters
{
    public class StateToStringConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            UserControl usr = (UserControl) value;

            if (usr is HomeView)
                return "Home";

            if (usr is EarthView)
                return "Earth View";


            if (usr is AnalzyeView)
                return "Analyze";

            return "";
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
