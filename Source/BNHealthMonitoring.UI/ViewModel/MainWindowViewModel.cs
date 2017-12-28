using System;
using System.Collections.ObjectModel;
using System.Reactive;
using System.Reactive.Linq;
using BNHealthMonitoring.UI.BL;
using BNHealthMonitoring.UI.Model;
using GalaSoft.MvvmLight;

namespace BNHealthMonitoring.UI.ViewModel
{
    public class MainWindowViewModel : ViewModelBase
    {

        private readonly MessageService m_messageService;
        private readonly DataState m_dataState;

        public MainWindowViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_messageService = MessageService.GetInsatnce();
            m_dataState.ComponentsUpdate.ObserveOnDispatcher().Subscribe(onComponentsUpdateEvent);
            m_messageService.RequestComponents();
        }

        public ObservableCollection<Component> Components
        {
            get { return m_dataState.Components; }
        }

        private void onComponentsUpdateEvent(Unit p_unit)
        {
            RaisePropertyChanged(() => Components);
        }
    }
}
