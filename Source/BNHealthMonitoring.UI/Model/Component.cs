using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BNHealthMonitoring.UI.Model
{
    public class Component
    {
        public Component()
        {
            Children = new List<Component>();
        }

        public string Name { get; set; }
        public int State { get; set; }
        public IList<Component> Children { get; set; }
    }
}
