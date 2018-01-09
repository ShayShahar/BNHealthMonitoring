using System.Collections.ObjectModel;
using Caliburn.Micro;
using HelixToolkit.Wpf;

namespace BNHealthMonitoring.UI.Model
{
    public class Component : PropertyChangedBase
    {
        private bool m_isExpanded;

        public Component()
        {
            Children = new ObservableCollection<Component>();
            Links =new ObservableCollection<Link>();
        }

        public bool IsExpanded
        {
            get { return m_isExpanded; }
            set
            {
                m_isExpanded = value;
                NotifyOfPropertyChange(()=> IsExpanded);
            }
        }
        public double Weight { get; set; }
        public string Name { get; set; }
        public string State { get; set; }
        public ObservableCollection<Component> Children { get; set; }
        public ObservableCollection<Link> Links { get; set; }

        public override bool Equals(object p_obj)
        {
            if (p_obj != null)
            {
                Component p = p_obj as Component;
                if (p == null)
                    return false;

                if (p.Name == Name)
                    return true;
            }
            return false;
        }


    }
}
