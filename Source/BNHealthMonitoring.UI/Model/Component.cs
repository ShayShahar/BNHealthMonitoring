using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Caliburn.Micro;

namespace BNHealthMonitoring.UI.Model
{
    public class Component : PropertyChangedBase
    {
        public Component()
        {
            Children = new ObservableCollection<Component>();
        }

        public string Name { get; set; }
        public int State { get; set; }
        public ObservableCollection<Component> Children { get; set; }

        public override bool Equals(object obj)
        {
            if (obj != null)
            {
                Component p = obj as Component;
                if (p == null)
                    return false;

                if (p.Name == Name)
                    return true;
            }
            return false;
        }
    }
}
