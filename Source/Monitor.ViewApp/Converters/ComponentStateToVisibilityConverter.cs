﻿namespace Monitor.ViewApp.Converters
{
    using System;
    using System.Globalization;
    using System.Windows;
    using System.Windows.Data;

    /// <summary>
    ///     ComponentStateToVisibilityConverter is an helper class for WPF MVVM pattern.
    ///     This converter converts between component's state to System.Visibility.
    /// </summary>
    public class ComponentStateToVisibilityConverter : IValueConverter
    {
        #region Public Methods and Operators

        public object Convert(object p_value, Type p_targetType, object p_parameter, CultureInfo p_culture)
        {
            if (p_value == null)
            {
                return Visibility.Collapsed;
            }

            var str = p_value.ToString();

            if (str == string.Empty)
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