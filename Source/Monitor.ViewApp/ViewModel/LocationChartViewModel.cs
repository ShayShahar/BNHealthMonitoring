namespace Monitor.ViewApp.ViewModel
{
    using System;
    using System.Collections.Generic;
    using System.Reactive.Linq;
    using System.Windows.Media;

    using BL;

    using GalaSoft.MvvmLight;

    using LiveCharts;
    using LiveCharts.Defaults;
    using LiveCharts.Wpf;

    /// <summary>
    ///     LocationChartViewModel class stores the logic & data of the LocationChartView.
    ///     The main goal of the LocationChartViewModel is to link between the data which related to the satellite's location
    ///     to the UI components.
    ///     This class inherits from Galasoft.MvvmLight.ViewModelBase which is the base class for any ViewModel in MVVM
    ///     pattern.
    /// </summary>
    public class LocationChartViewModel : ViewModelBase
    {
        #region Fields

        private readonly DataState m_dataState;
        private List<int> m_lables;

        #endregion

        #region Constructors and Destructors

        public LocationChartViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_dataState.LocationDeltaUpdated.ObserveOnDispatcher().Subscribe(onLocationUpdate);
            Labels = new List<int> {0, 5, 10};
            LocationData = new SeriesCollection
            {
                new LineSeries
                {
                    Title = "DELTA",
                    Values = new ChartValues<ObservablePoint>(),
                    PointGeometry = DefaultGeometries.Circle,
                    PointGeometrySize = 10,
                    StrokeThickness = 1.5,
                    LineSmoothness = 1,
                    PointForeground = new SolidColorBrush(Color.FromRgb(155, 89, 182)) {Opacity = 0.7},
                    Stroke = new SolidColorBrush(Color.FromRgb(155, 89, 182)) {Opacity = 1},
                    Fill = new SolidColorBrush(Color.FromRgb(189, 195, 199)) {Opacity = 0.2}
                }
            };
        }

        #endregion

        #region Public Properties

        public List<int> Labels
        {
            get { return m_lables; }
            set
            {
                m_lables = value;
                RaisePropertyChanged();
            }
        }

        public SeriesCollection LocationData { get; }

        #endregion

        #region Methods

        private void onLocationUpdate(Tuple<int, double> p_data)
        {
            if (LocationData[0].Values.Count == 5)
            {
                LocationData[0].Values.RemoveAt(0);
            }

            LocationData[0].Values.Add(new ObservablePoint(p_data.Item1, Math.Round(p_data.Item2, 2)));
            RaisePropertyChanged(() => LocationData);
        }

        #endregion
    }
}