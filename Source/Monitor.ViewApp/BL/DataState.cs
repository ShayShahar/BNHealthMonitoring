namespace Monitor.ViewApp.BL
{
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

    /// <summary>
    /// DataState class stores all the logic & user data.  
    /// In order to get an instance of DataState you should call the "GetInstance" method.  
    /// Note that this class implements the singleton pattern, which restricts the instantiation of the class to one object.
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

        /// <summary>
        /// Prevents a default instance of the <see cref="DataState"/> class from being created.
        /// </summary>
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


        /// <summary>
        /// Gets or sets the reflected components list.
        /// </summary>
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

        /// <summary>
        /// Gets the actual components list for the algorithm's output.
        /// </summary>
        public IList<Component> ComponentsList { get; }

        /// <summary>
        /// Subscribe for a component update event.
        /// </summary>
        public IObservable<Unit> ComponentsUpdate
        {
            get { return m_componentsUpdated; }
        }

        /// <summary>
        /// Gets or sets the current view.
        /// </summary>
        public UserControl CurrentView
        {
            get { return m_currentView; }
            set
            {
                m_currentView = value;
                m_viewChanged.OnNext(new Unit());
            }
        }

        /// <summary>
        /// Gets the log messages collection.
        /// </summary>
        public ObservableCollection<LogItem> IncomingMessagesLog { get; }

        /// <summary>
        /// Subscribe for delta update event.
        /// </summary>
        public IObservable<Tuple<int, double>> LocationDeltaUpdated
        {
            get { return m_locationDeltaUpdate; }
        }

        /// <summary>
        /// Subscribe for location update event.
        /// </summary>
        public IObservable<Point3D> LocationUpdated
        {
            get { return m_locationUpdate; }
        }

        /// <summary>
        /// Subscribe for log message update.
        /// </summary>
        public IObservable<Unit> LogMessageUpdate
        {
            get { return m_logUpdate; }
        }

        /// <summary>
        /// Gets or sets the selected component in the tree view.
        /// </summary>
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

        /// <summary>
        /// Subscribe for selected component changed event.
        /// </summary>
        public IObservable<Unit> SelectedComponentChangedEvent
        {
            get { return m_selectedComponentChanged; }
        }

        /// <summary>
        /// Subscribe for view changed event.
        /// </summary>
        public IObservable<Unit> ViewChanged
        {
            get { return m_viewChanged; }
        }

        #endregion

        #region Public Methods and Operators

        /// <summary>
        /// Gets an instance of DataState.
        /// </summary>
        /// <returns>DataState.</returns>
        public static DataState GetInstance()
        {
            return s_dataState ?? (s_dataState = new DataState());
        }

        /// <summary>
        /// Adds the message to log.
        /// </summary>
        /// <param name="p_message">The message</param>
        /// <param name="p_sender">Sender's name</param>
        public void AddMessageToLog(string p_message, string p_sender)
        {
            Application.Current.Dispatcher.Invoke(() => addMessageToLog(p_message, p_sender));
        }

        /// <summary>
        /// Update the reflected components list
        /// </summary>
        /// <param name="p_components">Components list message</param>
        public void SetComponents(CDMMessage p_components)
        {
            Application.Current.Dispatcher.Invoke(() => addComponent(m_components, p_components.CdmRoot));
            m_componentsUpdated.OnNext(new Unit());
        }

        /// <summary>
        /// Updates the algorithm output in log.
        /// </summary>
        /// <param name="p_result">The algorithm's result</param>
        public void UpdateAlgorithmOutput(OutputMessage p_result)
        {
            AddMessageToLog(
                string.Format("Selected component: {0}, State: {1}", p_result.Component.Name, p_result.Component.State),
                "CDM");
        }

        /// <summary>
        /// Updates the satellite's location.
        /// </summary>
        /// <param name="p_location">Geocentric coordinates X,Y,Z</param>
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

        /// <summary>
        /// Updates the LRU output in log.
        /// </summary>
        /// <param name="p_result">The LRU result</param>
        public void UpdateLruResult(OutputMessage p_result)
        {
            AddMessageToLog(
                string.Format("Selected component: {0}, State: {1}", p_result.Component.Name, p_result.Component.State),
                "LRU");
        }

        #endregion

        #region Methods

        /// <summary>
        /// Adds component to the reflected components list
        /// </summary>
        /// <param name="p_list">The components list</param>
        /// <param name="p_component">The component</param>
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
                        DestinationName = c.Children.Name == string.Empty ? component.Name : c.Children.Name,
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

        /// <summary>
        /// Adds the message to log.
        /// Invoked on dispatcher thread.
        /// </summary>
        /// <param name="p_message">The message</param>
        /// <param name="p_sender">Sender's name</param>
        private void addMessageToLog(string p_message, string p_sender)
        {
            IncomingMessagesLog.Add(new LogItem {Message = p_message, Sender = p_sender});
            m_logUpdate.OnNext(new Unit());
        }

        #endregion
    }
}