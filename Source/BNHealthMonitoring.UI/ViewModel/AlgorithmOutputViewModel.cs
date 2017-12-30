using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using BNHealthMonitoring.UI.BL;
using GalaSoft.MvvmLight;
using LiveCharts;
using LiveCharts.Wpf;

namespace BNHealthMonitoring.UI.ViewModel
{
    public class AlgorithmOutputViewModel : ViewModelBase
    {
        private readonly DataState m_dataState;

        public AlgorithmOutputViewModel()
        {
            m_dataState = DataState.GetInstance();

            Results = new SeriesCollection
            {
                new ColumnSeries
                {
                    Title = "%",
                    Values = new ChartValues<double> {10, 50, 35, 50},
                    PointGeometry = DefaultGeometries.Circle,
                    StrokeThickness = 2,
                    Stroke =  new SolidColorBrush(Color.FromRgb(255,23,68)) {Opacity = 1},
                    Fill = new SolidColorBrush(Color.FromRgb(255,23,68)) {Opacity = 1}
                }
            };

            Labels = new List<int>() {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
            Components = new List<string>() {"A", "B"};
        }

        public SeriesCollection Results { get; set; }
        public IList<string> Components { get; set; }

        public IList<int> Labels { get; set; } 
    }
}
