namespace Monitor.ViewApp.ViewModel
{
    using System;
    using System.Collections.ObjectModel;
    using System.Reactive;
    using System.Reactive.Linq;
    using GalaSoft.MvvmLight;
    using BL;
    using Model;


    /// <summary>
    ///     ProbabilityTableViewModel class stores the logic & data of the ProbabilityTableView.
    ///     The main goal of the ProbabilityTableViewModel is to link between the data which related to the selected component's dependencies
    ///     to the UI components.
    ///     This class inherits from Galasoft.MvvmLight.ViewModelBase which is the base class for any ViewModel in MVVM
    ///     pattern.
    /// </summary>
    public class ProbabilityTableViewModel : ViewModelBase
    {
        #region Fields

        private readonly DataState m_dataState;

        #endregion

        #region Constructors and Destructors

        /// <summary>
        /// Initializes a new instance of the <see cref="ProbabilityTableViewModel"/> class.
        /// </summary>
        public ProbabilityTableViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_dataState.ComponentsUpdate.ObserveOnDispatcher().Subscribe(onComponentsUpdateEvent);
            m_dataState.SelectedComponentChangedEvent.ObserveOnDispatcher().Subscribe(onSelectionChanged);
        }

        #endregion

        #region Public Properties

        /// <summary>
        /// Gets a value indicating whether there is available data for the selected component
        /// </summary>
        /// <value><c>true</c> if the data available; otherwise, <c>false</c>.</value>
        public bool IsDataAvailable
        {
            get { return !IsDataNotAvailable; }
        }

        public bool IsDataNotAvailable
        {
            get
            {
                if (SelectedComponent == null)
                    return true;
                return SelectedComponent.Count == 0;
            }
        }

        /// <summary>
        /// Gets the selected component.
        /// </summary>
        /// <value>The selected component.</value>
        public ObservableCollection<Link> SelectedComponent
        {
            get { return m_dataState.SelectedComponent?.Links; }
        }

        #endregion

        #region Methods


        /// <summary>
        /// This function invokes where there is a change in the components' data in the DataState.
        /// </summary>
        private void onComponentsUpdateEvent(Unit p_unit)
        {
            RaisePropertyChanged(() => IsDataNotAvailable);
            RaisePropertyChanged(() => SelectedComponent);
        }

        /// <summary>
        /// This function invokes where the user selects a component in the components tree.
        /// </summary>
        private void onSelectionChanged(Unit p_unit)
        {
            RaisePropertyChanged(() => SelectedComponent);
            RaisePropertyChanged(() => IsDataNotAvailable);
            RaisePropertyChanged(() => IsDataAvailable);
        }

        #endregion
    }
}