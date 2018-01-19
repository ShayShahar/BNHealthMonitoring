using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Reactive;
using System.Reactive.Subjects;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Media3D;
using HealthMonitoringMessages;
using Monitor.ViewApp.Model;

namespace Monitor.ViewApp.BL
{
    /// <summary>
    ///     DataState class stores all the logic & user data.
    ///     In order to get an instance of DataState you should call the "GetInstacne" method.
    ///     Note that this class implemented the singleton pattern, which restricts the instantiation of the class to one
    ///     object.
    /// </summary>
    public class DataState
    {
        #region Static Fields

        private static DataState s_dataState;

        #endregion

        #region Fields

        private readonly ISubject<Unit> m_componentsUpdated;
        private readonly ISubject<Tuple<int, double>> m_locationDeltaUpdate;
        private readonly ISubject<Point3D> m_locationUpdate;
        private readonly ISubject<Unit> m_logUpdate;
        private readonly ISubject<Unit> m_selectedComponentChanged;
        private ObservableCollection<Component> m_components;
        private UserControl m_currentView;
        private double m_px;
        private double m_py;
        private double m_pz;
        private Component m_selectedComponent;
        private readonly ISubject<Unit> m_viewChanged;

        #endregion

        #region Constructors and Destructors

        private DataState()
        {
            m_locationDeltaUpdate = new Subject<Tuple<int, double>>();
            m_locationUpdate = new Subject<Point3D>();
            m_componentsUpdated = new Subject<Unit>();
            m_logUpdate = new Subject<Unit>();
            m_selectedComponentChanged = new Subject<Unit>();
            m_components = new ObservableCollection<Component>();
            IncomingMessagesLog = new ObservableCollection<LogItem>();
            m_viewChanged = new Subject<Unit>();
            ComponentsList = new List<Component>();

            m_px = 0;
            m_py = 0;
            m_pz = 0;
        }

        #endregion

        #region Public Properties

        public ObservableCollection<Component> Components
        {
            get { return m_components; }
            set
            {
                if (value.SequenceEqual(m_components))
                    return;

                m_components = value;
                m_componentsUpdated.OnNext(new Unit());
            }
        }

        public IList<Component> ComponentsList { get; }

        public IObservable<Unit> ComponentsUpdate
        {
            get { return m_componentsUpdated; }
        }

        public UserControl CurrentView
        {
            get { return m_currentView; }
            set
            {
                m_currentView = value;
                m_viewChanged.OnNext(new Unit());
            }
        }

        public ObservableCollection<LogItem> IncomingMessagesLog { get; }

        public IObservable<Tuple<int, double>> LocationDeltaUpdated
        {
            get { return m_locationDeltaUpdate; }
        }

        public IObservable<Point3D> LocationUpdated
        {
            get { return m_locationUpdate; }
        }

        public IObservable<Unit> LogMessageUpdate
        {
            get { return m_logUpdate; }
        }

        public Component SelectedComponent
        {
            get { return m_selectedComponent; }
            set
            {
                if (m_selectedComponent != null && m_selectedComponent.Equals(value))
                {
                    return;
                }

                m_selectedComponent = value;
                m_selectedComponentChanged.OnNext(new Unit());
            }
        }

        public IObservable<Unit> SelectedComponentChangedEvent
        {
            get { return m_selectedComponentChanged; }
        }

        public IObservable<Unit> ViewChanged
        {
            get { return m_viewChanged; }
        }

        #endregion

        #region Public Methods and Operators

        public static DataState GetInstance()
        {
            return s_dataState ?? (s_dataState = new DataState());
        }

        public void AddMessageToLog(string p_message, string p_sender)
        {
            Application.Current.Dispatcher.Invoke(() => addMessageToLog(p_message, p_sender));
        }

        public void SetComponents(CDMMessage p_components)
        {
            Application.Current.Dispatcher.Invoke(() => addComponent(m_components, p_components.CdmRoot));
            m_componentsUpdated.OnNext(new Unit());
        }

        public void UpdateAlgorithmOutput(OutputMessage p_result)
        {
            AddMessageToLog(
                string.Format("Selected component: {0}, State: {1}", p_result.Component.Name, p_result.Component.State),
                "CDM");
        }

        public void UpdateLocation(LocationMessage p_location)
        {
            m_locationDeltaUpdate.OnNext(new Tuple<int, double>(p_location.Seconds, p_location.Delta));

            m_px = p_location.X;
            m_py = p_location.Y;
            m_pz = p_location.Z;
            m_locationUpdate.OnNext(new Point3D(m_px, m_py, m_pz));
            AddMessageToLog(
                string.Format("Satellite location: ({0}, {1}, {2})", Math.Round(m_px, 2), Math.Round(m_py, 2),
                    Math.Round(m_pz, 2)), "GPS");
        }

        public void UpdateLruResult(OutputMessage p_result)
        {
            AddMessageToLog(
                string.Format("Selected component: {0}, State: {1}", p_result.Component.Name, p_result.Component.State),
                "LRU");
        }

        #endregion

        #region Methods

        private void addComponent(ObservableCollection<Component> p_list, pComponent p_component)
        {
            var component =
                p_list.FirstOrDefault(
                    p_c => p_component.Name.Equals(p_c.Name, StringComparison.InvariantCultureIgnoreCase));

            if (component == null)
            {
                component = new Component
                {
                    Name = p_component.Name,
                    State = p_component.State,
                    Weight = Math.Round(p_component.Weight, 2),
                    Children = new ObservableCollection<Component>()
                };

                ComponentsList.Add(component);
                p_list.Add(component);
            }
            else
            {
                component.State = p_component.State;
                component.Weight = Math.Round(p_component.Weight, 2);
            }

            foreach (var c in p_component.LinksList)
            {
                var link =
                    component.Links.FirstOrDefault(p_l => p_l.ChildrenName == c.Children.Name);

                if (link == null)
                {
                    component.Links.Add(new Link
                    {
                        ResponsibleComponent = component,
                        ChildrenName = c.Children.Name,
                        DestenationName = c.Children.Name == string.Empty ? component.Name : c.Children.Name,
                        Probability = c.Probability
                    });
                }
                else
                {
                    link.Probability = c.Probability;
                }

                if (c.HasChildren)
                    addComponent(component.Children, c.Children);
            }
        }

        private void addMessageToLog(string p_message, string p_sender)
        {
            IncomingMessagesLog.Add(new LogItem {Message = p_message, Sender = p_sender});
            m_logUpdate.OnNext(new Unit());
        }

        #endregion
    }
}