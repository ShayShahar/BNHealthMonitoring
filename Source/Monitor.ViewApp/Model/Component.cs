using System.Collections.ObjectModel;
using Caliburn.Micro;

namespace Monitor.ViewApp.Model
{
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

        public Component()
        {
            Children = new ObservableCollection<Component>();
            Links = new ObservableCollection<Link>();
        }

        #endregion

        #region Public Properties

        public ObservableCollection<Component> Children { get; set; }

        public bool IsExpanded
        {
            get { return m_isExpanded; }
            set
            {
                m_isExpanded = value;
                NotifyOfPropertyChange(() => IsExpanded);
            }
        }

        public ObservableCollection<Link> Links { get; set; }
        public string Name { get; set; }
        public string State { get; set; }
        public double Weight { get; set; }

        #endregion

        #region Public Methods and Operators

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