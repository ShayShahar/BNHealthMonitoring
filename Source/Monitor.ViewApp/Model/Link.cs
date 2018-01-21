namespace Monitor.ViewApp.Model
{
    using System;

    using Caliburn.Micro;

    /// <summary>
    ///     Link class stores the component's dependencies.
    ///     The class inherits from PropertyChangedBase -> Caliburn.Micro helper which implements INotifyPropertyChanged
    ///     in order to update the UI when there is a change in the data.
    /// </summary>
    public class Link : PropertyChangedBase
    {
        #region Fields

        private double m_probability;

        #endregion

        #region Public Properties

        public string ChildrenName { get; set; }

        public string DestenationName { get; set; }

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

        public Component ResponsibleComponent { get; set; }

        public string State { get; set; }

        #endregion
    }
}