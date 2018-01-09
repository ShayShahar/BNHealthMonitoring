using System;
using System.Collections.ObjectModel;
using System.Reactive;
using System.Reactive.Linq;
using System.Windows.Input;
using BNHealthMonitoring.UI.BL;
using BNHealthMonitoring.UI.Model;
using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;

namespace BNHealthMonitoring.UI.ViewModel
{
    public class ComponentsTreeViewModel : ViewModelBase
    {
        private readonly DataState m_dataState;

        public ComponentsTreeViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_dataState.ComponentsUpdate.ObserveOnDispatcher().Subscribe(onComponentsUpdateEvent);
            m_dataState.SelectedComponentChangedEvent.ObserveOnDispatcher().Subscribe(onSelectionChanged);
        }

        public ObservableCollection<Component> Components
        {
            get { return m_dataState.Components; }
        }

        private void onComponentsUpdateEvent(Unit p_unit)
        {
            RaisePropertyChanged(() => Components);
            RaisePropertyChanged(() => IsLoaded);
        }

        private void onSelectionChanged(Unit p_unit)
        {
            RaisePropertyChanged(() => Weight);
            RaisePropertyChanged(() => State);
            RaisePropertyChanged(() => IsComponentNotSelected);
        }

        public bool IsComponentNotSelected
        {
            get { return m_dataState.SelectedComponent == null; }
        }

        public double? Weight
        {
            get { return m_dataState.SelectedComponent?.Weight; }
        }

        public string State
        {
            get { return m_dataState.SelectedComponent?.State; }
        }

        public bool IsLoaded
        {
            get { return Components.Count > 0; }
        }
    }
}
