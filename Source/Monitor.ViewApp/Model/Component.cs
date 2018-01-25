namespace Monitor.ViewApp.Model
{
    using System.Collections.ObjectModel;

    using Caliburn.Micro;

    /// <summary>
    ///     Component class stores the component data.
    ///     The class inherits from PropertyChangedBase -> Caliburn.Micro helper which implements INotifyPropertyChanged
    ///     in order to update the UI when there is a change in the data.
    /// </summary>
    public class Component : PropertyChangedBase
    {
        #region Fields

        private bool m_isExpanded;

        #endregion

        #region Constructors and Destructors


        /// <summary>
        /// Initializes a new instance of the <see cref="Component"/> class.
        /// </summary>
        public Component()
        {
            Children = new ObservableCollection<Component>();
            Links = new ObservableCollection<Link>();
        }

        #endregion

        #region Public Properties

        /// <summary>
        /// Gets or sets the children nodes of the component.
        /// </summary>
        public ObservableCollection<Component> Children { get; set; }


        /// <summary>
        /// Gets or sets a value indicating whether this component is expanded in the tree view.
        /// </summary>
        /// <value><c>true</c> if this instance is expanded; otherwise, <c>false</c>.</value>
        public bool IsExpanded
        {
            get { return m_isExpanded; }
            set
            {
                m_isExpanded = value;
                NotifyOfPropertyChange(() => IsExpanded);
            }
        }

        /// <summary>
        /// Gets or sets the conditional dependencies of the component.
        /// </summary>
        /// <value>The links.</value>
        public ObservableCollection<Link> Links { get; set; }

        /// <summary>
        /// Gets or sets the component's name.
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// Gets or sets the component's state.
        /// </summary>
        public string State { get; set; }

        /// <summary>
        /// Gets or sets the component's weight.
        /// </summary>
        /// <value>The weight.</value>
        public double Weight { get; set; }

        #endregion

        #region Public Methods and Operators

        /// <summary>
        /// Compare between two components' instances.
        /// </summary>
        /// <param name="p_obj">The Component object</param>
        /// <returns><c>true</c> if this objects are equals; otherwise, <c>false</c>.</returns>
        public override bool Equals(object p_obj)
        {
            if (p_obj != null)
            {
                var p = p_obj as Component;
                if (p == null)
                    return false;

                if (p.Name == Name)
                    return true;
            }
            return false;
        }

        #endregion
    }
}