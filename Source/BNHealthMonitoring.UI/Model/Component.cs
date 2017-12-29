using System.Collections.ObjectModel;
using Caliburn.Micro;

namespace BNHealthMonitoring.UI.Model
{
    public class Component : PropertyChangedBase
    {
        public Component()
        {
            Children = new ObservableCollection<Component>();
            Links =new ObservableCollection<Link>();
        }

        public string Name { get; set; }
        public int State { get; set; }
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
