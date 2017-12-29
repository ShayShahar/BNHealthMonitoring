using System;
using System.Collections.ObjectModel;
using System.Reactive;
using System.Reactive.Linq;
using BNHealthMonitoring.UI.BL;
using BNHealthMonitoring.UI.Model;
using GalaSoft.MvvmLight;

namespace BNHealthMonitoring.UI.ViewModel
{
    public class ComponentsTreeViewModel : ViewModelBase
    {
        private readonly DataState m_dataState;

        public ComponentsTreeViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_dataState.ComponentsUpdate.ObserveOnDispatcher().Subscribe(onComponentsUpdateEvent);
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

        public bool IsLoaded
        {
            get { return Components.Count > 0; }
        }
    }
}
