using System;
using System.Collections.ObjectModel;
using System.Reactive;
using System.Reactive.Linq;
using GalaSoft.MvvmLight;
using Monitor.ViewApp.BL;
using Monitor.ViewApp.Model;

namespace Monitor.ViewApp.ViewModel
{
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

        public ProbabilityTableViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_dataState.ComponentsUpdate.ObserveOnDispatcher().Subscribe(onComponentsUpdateEvent);
            m_dataState.SelectedComponentChangedEvent.ObserveOnDispatcher().Subscribe(onSelectionChanged);
        }

        #endregion

        #region Public Properties

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

        public ObservableCollection<Link> SelectedComponent
        {
            get { return m_dataState.SelectedComponent?.Links; }
        }

        #endregion

        #region Methods

        private void onComponentsUpdateEvent(Unit p_unit)
        {
            RaisePropertyChanged(() => IsDataNotAvailable);
            RaisePropertyChanged(() => SelectedComponent);
        }

        private void onSelectionChanged(Unit p_unit)
        {
            RaisePropertyChanged(() => SelectedComponent);
            RaisePropertyChanged(() => IsDataNotAvailable);
            RaisePropertyChanged(() => IsDataAvailable);
        }

        #endregion
    }
}