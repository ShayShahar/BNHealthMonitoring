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

        /// <summary>
        /// Gets or sets the name of the children.
        /// </summary>
        public string ChildrenName { get; set; }

        /// <summary>
        /// Gets or sets the name of the destination.
        /// </summary>
        public string DestinationName { get; set; }

        /// <summary>
        /// Gets or sets the transition's probability.
        /// </summary>
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

        /// <summary>
        /// Gets or sets the component which owns the link.
        /// </summary>
        public Component ResponsibleComponent { get; set; }
        #endregion
    }
}