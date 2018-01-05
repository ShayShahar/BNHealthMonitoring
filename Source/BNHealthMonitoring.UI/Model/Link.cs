using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Animation;
using Caliburn.Micro;

namespace BNHealthMonitoring.UI.Model
{
    public class Link : PropertyChangedBase
    {
        private double m_probability;

        public Component ResponsibleComponent { get; set; }

        public double Probability
        {
            get
            {
                return m_probability;
            }
            set { m_probability = Math.Round(value, 2); }
        }

        public string DestenationName { get; set; }
        public string State { get; set; }

        public bool IsCurrentState
        {
            get { return ResponsibleComponent.State == State; }
        }
    }
}
