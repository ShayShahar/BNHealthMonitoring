namespace Monitor.ViewApp.Converters
{
    using System;
    using System.Globalization;
    using System.Windows;
    using System.Windows.Data;

    /// <summary>
    ///     BooleanToVisibilityConverter is an helper class for WPF MVVM pattern.
    ///     This converter converts between boolean data to System.Visibility.
    /// </summary>
    public class BooleanToVisibilityConverter : IValueConverter
    {
        #region Public Methods and Operators

        public object Convert(object p_value, Type p_targetType, object p_parameter, CultureInfo p_culture)
        {
            if (p_value == null)
            {
                return Visibility.Collapsed;
            }

            var val = (bool) p_value;

            if (val)
            {
                return Visibility.Collapsed;
            }

            return Visibility.Visible;
        }

        public object ConvertBack(object p_value, Type p_targetType, object p_parameter, CultureInfo p_culture)
        {
            throw new NotImplementedException();
        }

        #endregion
    }
}