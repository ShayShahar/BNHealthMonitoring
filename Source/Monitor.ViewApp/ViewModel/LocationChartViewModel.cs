using System;
using System.Collections.Generic;
using System.Reactive.Linq;
using System.Windows.Media;
using GalaSoft.MvvmLight;
using LiveCharts;
using LiveCharts.Defaults;
using LiveCharts.Wpf;
using Monitor.ViewApp.BL;

namespace Monitor.ViewApp.ViewModel
{
    public class LocationChartViewModel : ViewModelBase
    {
        private readonly DataState m_dataState;
        private readonly SeriesCollection m_locationDelta;
        private List<int> m_lables;

        public LocationChartViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_dataState.LocationDeltaUpdated.ObserveOnDispatcher().Subscribe(onLocationUpdate);
            Labels = new List<int>() {0, 5, 10};
            m_locationDelta = new SeriesCollection
            {
                new LineSeries
                {
                    Title = "DELTA",
                    Values = new ChartValues<ObservablePoint>(),
                    PointGeometry = DefaultGeometries.Circle,
                    PointGeometrySize = 10,
                    StrokeThickness = 1.5,
                    LineSmoothness = 1,
                    PointForeground = new SolidColorBrush(Color.FromRgb(155,89,182)) {Opacity = 0.7},
                    Stroke = new SolidColorBrush(Color.FromRgb(155,89,182)) {Opacity = 1},
                    Fill = new SolidColorBrush(Color.FromRgb(189,195,199)) {Opacity = 0.2}
                }
            };
        }

        private void onLocationUpdate(Tuple<int, double> p_data)
        {
            if (m_locationDelta[0].Values.Count == 5)
            {
                m_locationDelta[0].Values.RemoveAt(0);
            }
            
            m_locationDelta[0].Values.Add(new ObservablePoint(p_data.Item1, Math.Round(p_data.Item2, 2)));
            RaisePropertyChanged(() => LocationData);
        }
        public SeriesCollection LocationData
        {
            get { return m_locationDelta; }
        }

        public List<int> Labels
        {
            get { return m_lables; }
            set
            {
                m_lables = value;
                RaisePropertyChanged();
            }
        }
    }
}
