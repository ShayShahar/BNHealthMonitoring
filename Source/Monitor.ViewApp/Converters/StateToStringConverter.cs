using System;
using System.Globalization;
using System.Windows.Controls;
using System.Windows.Data;
using Monitor.ViewApp.View;

namespace Monitor.ViewApp.Converters
{
    /// <summary>
    ///     StateToStringConverter is an helper class for WPF MVVM pattern.
    ///     This converter converts between the current view's state to string.
    /// </summary>
    public class StateToStringConverter : IValueConverter
    {
        #region Public Methods and Operators

        public object Convert(object p_value, Type p_targetType, object p_parameter, CultureInfo p_culture)
        {
            var usr = (UserControl) p_value;

            if (usr is HomeView)
                return "Home";

            if (usr is EarthView)
                return "Earth View";

            return "";
        }

        public object ConvertBack(object p_value, Type p_targetType, object p_parameter, CultureInfo p_culture)
        {
            throw new NotImplementedException();
        }

        #endregion
    }
}