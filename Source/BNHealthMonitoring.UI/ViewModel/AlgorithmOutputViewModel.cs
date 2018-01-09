using System;
using System.Collections.Generic;
using System.Linq;
using System.Reactive;
using System.Reactive.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using BNHealthMonitoring.UI.BL;
using BNHealthMonitoring.UI.Model;
using GalaSoft.MvvmLight;
using LiveCharts;
using LiveCharts.Configurations;
using LiveCharts.Defaults;
using LiveCharts.Wpf;
using LiveCharts.Wpf.Points;

namespace BNHealthMonitoring.UI.ViewModel
{
    public class AlgorithmOutputViewModel : ViewModelBase
    {
        private readonly DataState m_dataState;

        public SeriesCollection Results { get; set; }
        public Dictionary<string, int> Components { get; set; }
        public IList<int> Labels { get; set; }
        public Brush DangerBrush { get; set; }
        public Brush WarningBrush { get; set; }
        public Brush OkBrush { get; set; }
        public CartesianMapper<ObservableValue> Mapper { get; set; }

        public AlgorithmOutputViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_dataState.ComponentsUpdate.ObserveOnDispatcher().Subscribe(onComponentsUpdateEvent);

            DangerBrush = new SolidColorBrush(Color.FromRgb(238, 83, 80));
            WarningBrush = new SolidColorBrush(Color.FromRgb(241, 196, 15));
            OkBrush = new SolidColorBrush(Color.FromRgb(46, 204, 113));

            Mapper = Mappers.Xy<ObservableValue>().X((p_item, p_index) => p_index)
           .Y(p_item => p_item.Value)
           .Fill(p_item => p_item.Value >= 70 ? DangerBrush : (p_item.Value >= 50 ? WarningBrush : OkBrush))
           .Stroke(p_item => p_item.Value >= 70 ? DangerBrush : (p_item.Value >= 50 ? WarningBrush : OkBrush));

            Components = new Dictionary<string, int>();

            Results = new SeriesCollection{
            {
                new ColumnSeries
                {
                    Title = "%",
                    Values = new ChartValues<ObservableValue>(),
                    PointGeometry = DefaultGeometries.Circle,
                    StrokeThickness = 2,
                    Configuration = Mapper,
                    //Stroke =  new SolidColorBrush(Color.FromRgb(46,204,113)) {Opacity = 1},
                    //Fill = new SolidColorBrush(Color.FromRgb(46,204,113)) {Opacity = 1}
                }
            }};

            Labels = new List<int>() { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
        }

        public List<string> Keys
        {
            get { return Components.Keys.ToList(); }
        }

        private void onComponentsUpdateEvent(Unit p_unit)
        {
            var components = m_dataState.ComponentsList.Where(p_c => p_c.Children.Count == 0).ToList();
            if (!components.Any())
                return;

            double total = components.Sum(p_component => p_component.Weight);

            foreach (var component in components)
            {
                if (!Components.ContainsKey(component.Name))
                {
                    Components.Add(component.Name, Components.Count + 1);
                    Results[0].Values.Add(new ObservableValue(Math.Round((component.Weight / total) * 100, 2)));
                    RaisePropertyChanged(() => Keys);
                }
                else
                {
                    var val = Results[0].Values[Components[component.Name] - 1];
                    ObservableValue value = val as ObservableValue;
                    if (value != null)
                        value.Value = Math.Round((component.Weight / total) * 100, 2);

                    //  Results[0].Values[Components[component.Name] - 1] = new ObservableValue((component.Weight / total) * 100);

                }
            }
        }

    }
}
