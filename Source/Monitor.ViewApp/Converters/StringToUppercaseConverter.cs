namespace Monitor.ViewApp.Converters
{
    using System;
    using System.Globalization;
    using System.Windows.Data;

    /// <summary>
    ///     StringToUppercaseConverter is an helper class for WPF MVVM pattern.
    ///     This converter switch all characters to UPPER-CASE
    /// </summary>
    public class StringToUppercaseConverter :  IValueConverter
    {
        public object Convert(object p_value, Type p_targetType, object p_parameter, CultureInfo p_culture)
        {
            string s = (string) p_value;
            return s?.ToUpper();
        }

        public object ConvertBack(object p_value, Type p_targetType, object p_parameter, CultureInfo p_culture)
        {
            throw new NotImplementedException();
        }
    }
}
