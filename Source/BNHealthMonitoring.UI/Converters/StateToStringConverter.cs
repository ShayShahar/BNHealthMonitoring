using System;
using System.Globalization;
using System.Windows.Controls;
using System.Windows.Data;
using Monitor.ViewApp.View;

namespace Monitor.ViewApp.Converters
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

            return "";
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
