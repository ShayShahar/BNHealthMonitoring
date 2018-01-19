using System;
using Caliburn.Micro;

namespace Monitor.ViewApp.Model
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
            set
            {
                m_probability = Math.Round(value, 2);
                NotifyOfPropertyChange(() => Probability);
            }
        }

        public string ChildrenName { get; set; }
        public string DestenationName { get; set; }
        public string State { get; set; }

    }
}
