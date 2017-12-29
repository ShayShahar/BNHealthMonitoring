using System;
using System.Collections.ObjectModel;
using System.Reactive;
using System.Reactive.Linq;
using BNHealthMonitoring.UI.BL;
using BNHealthMonitoring.UI.Model;
using GalaSoft.MvvmLight;

namespace BNHealthMonitoring.UI.ViewModel
{
    public class ProbabilityTableViewModel : ViewModelBase
    {
        private readonly DataState m_dataState;

        public ProbabilityTableViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_dataState.SelectedComponentChangedEvent.ObserveOnDispatcher().Subscribe(onSelectionChanged);
        }

        public ObservableCollection<Link> SelectedComponent
        {
            get
            {
                return m_dataState.SelectedComponent?.Links;
            }
        }

        public bool IsDataNotAvailable
        {
            get { return SelectedComponent?.Count == 0; }
        }
        public bool IsDataAvailable
        {
            get { return !IsDataNotAvailable; }
        }

        private void onSelectionChanged(Unit p_unit)
        {
            RaisePropertyChanged(() => SelectedComponent);
            RaisePropertyChanged(() => IsDataNotAvailable);
            RaisePropertyChanged(() => IsDataAvailable);
        }
    }
}
