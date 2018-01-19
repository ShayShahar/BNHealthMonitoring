using System;
using System.Collections.ObjectModel;
using System.Reactive;
using System.Reactive.Linq;
using GalaSoft.MvvmLight;
using Monitor.ViewApp.BL;
using Monitor.ViewApp.Model;

namespace Monitor.ViewApp.ViewModel
{
    public class ProbabilityTableViewModel : ViewModelBase
    {
        private readonly DataState m_dataState;

        public ProbabilityTableViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_dataState.ComponentsUpdate.ObserveOnDispatcher().Subscribe(onComponentsUpdateEvent);
            m_dataState.SelectedComponentChangedEvent.ObserveOnDispatcher().Subscribe(onSelectionChanged);
        }

        public ObservableCollection<Link> SelectedComponent
        {
            get
            {
                return m_dataState.SelectedComponent?.Links;
            }
        }

        private void onComponentsUpdateEvent(Unit p_unit)
        {
            RaisePropertyChanged(() => IsDataNotAvailable);
            RaisePropertyChanged(() => SelectedComponent);
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
