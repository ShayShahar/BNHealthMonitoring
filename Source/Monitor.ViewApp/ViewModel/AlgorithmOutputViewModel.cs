namespace Monitor.ViewApp.ViewModel
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Reactive;
    using System.Reactive.Linq;
    using System.Windows.Media;

    using BL;

    using GalaSoft.MvvmLight;

    using LiveCharts;
    using LiveCharts.Configurations;
    using LiveCharts.Defaults;
    using LiveCharts.Wpf;

    /// <summary>
    ///     AlgorithmOutputViewModel class stores the logic & data of the AlgorithmOutputView.
    ///     The main goal of the AlgorithmOutputViewModel is to link between the data which related to the health monitoring algorithm output
    ///     to the UI components.
    ///     This class inherits from Galasoft.MvvmLight.ViewModelBase which is the base class for any ViewModel in MVVM pattern.
    /// </summary>
    public class AlgorithmOutputViewModel : ViewModelBase
    {
        #region Fields

        private readonly DataState m_dataState;

        #endregion

        #region Constructors and Destructors

        /// <summary>
        /// Initializes a new instance of the <see cref="AlgorithmOutputViewModel"/> class.
        /// </summary>
        public AlgorithmOutputViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_dataState.ComponentsUpdate.ObserveOnDispatcher().Subscribe(this.onComponentsUpdateEvent);

            DangerBrush = new SolidColorBrush(Color.FromRgb(238, 83, 80));
            WarningBrush = new SolidColorBrush(Color.FromRgb(241, 196, 15));
            OkBrush = new SolidColorBrush(Color.FromRgb(46, 204, 113));

            Mapper = Mappers.Xy<ObservableValue>().X((p_item, p_index) => p_index)
                .Y(p_item => p_item.Value)
                .Fill(p_item => p_item.Value >= 15 ? DangerBrush : (p_item.Value >= 8 ? WarningBrush : OkBrush))
                .Stroke(p_item => p_item.Value >= 15 ? DangerBrush : (p_item.Value >= 8 ? WarningBrush : OkBrush));

            Components = new Dictionary<string, int>();

            Results = new SeriesCollection
            {
                new ColumnSeries
                {
                    Title = "Weight",
                    Values = new ChartValues<ObservableValue>(),
                    PointGeometry = DefaultGeometries.Circle,
                    StrokeThickness = 2,
                    Configuration = Mapper,
                    ColumnPadding = 3,
                    Stroke = new SolidColorBrush(Color.FromRgb(150, 150, 150)) {Opacity = 1},
                    Fill = new SolidColorBrush(Color.FromRgb(150, 150, 150)) {Opacity = 1}
                }
            };
        }

        #endregion

        #region Public Properties

        /// <summary>
        /// Gets or sets the components to weight map.
        /// </summary>
        public Dictionary<string, int> Components { get; set; }

        /// <summary>
        /// Gets the components' names from the components to weight map
        /// </summary>
        public List<string> Keys
        {
            get { return Components.Keys.ToList(); }
        }

        /// <summary>
        /// Gets or sets the mapper which is a value to color converter that changes the chart's color according to its value.
        /// </summary>
        public CartesianMapper<ObservableValue> Mapper { get; set; }

        /// <summary>
        /// Gets or sets the results collection.
        /// </summary>
        public SeriesCollection Results { get; set; }

        /// <summary>
        /// Gets or sets the OK state's bar color.
        /// </summary>
        public Brush OkBrush { get; set; }

        /// <summary>
        /// Gets or sets the warning state's bar color.
        /// </summary>
        public Brush WarningBrush { get; set; }

        /// <summary>
        /// Gets or sets the danger state's bar color.
        /// </summary>
        public Brush DangerBrush { get; set; }


        #endregion

        #region Methods

        /// <summary>
        /// This function invokes where there is a change in the components' data in the DataState.
        /// </summary>
        private void onComponentsUpdateEvent(Unit p_unit)
        {
            var components = m_dataState.ComponentsList.Where(p_c => p_c.Children.Count == 0).ToList();
            if (!components.Any())
                return;

            foreach (var component in components)
            {
                if (!Components.ContainsKey(component.Name))
                {
                    Components.Add(component.Name, Components.Count + 1);
                    Results[0].Values.Add(new ObservableValue(component.Weight));
                    RaisePropertyChanged(() => Keys);
                }
                else
                {
                    var val = Results[0].Values[Components[component.Name] - 1];
                    var value = val as ObservableValue;
                    if (value != null)
                        value.Value = component.Weight;
                }
            }
        }

        #endregion
    }
}