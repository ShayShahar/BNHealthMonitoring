using System;
using System.Globalization;
using System.Windows.Data;

namespace Monitor.ViewApp.Converters
{
    public class StringToUppercaseConverter :  IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            string s = (string) value;
            return s?.ToUpper();
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
