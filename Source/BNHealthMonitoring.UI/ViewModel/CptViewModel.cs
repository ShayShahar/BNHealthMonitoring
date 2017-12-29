using System;
using System.Collections.ObjectModel;
using System.Reactive;
using System.Reactive.Linq;
using BNHealthMonitoring.UI.BL;
using BNHealthMonitoring.UI.Model;
using GalaSoft.MvvmLight;

namespace BNHealthMonitoring.UI.ViewModel
{
    public class CptViewModel : ViewModelBase
    {
        private readonly MessageService m_messageService;
        private readonly DataState m_dataState;

        public CptViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_messageService = MessageService.GetInsatnce();
            m_dataState.SelectedComponentChangedEvent.ObserveOnDispatcher().Subscribe(onSelectionChanged);
        }

        public ObservableCollection<Link> SelectedComponent
        {
            get
            {
                return m_dataState.SelectedComponent?.Links;
            }
        }

        private void onSelectionChanged(Unit p_unit)
        {
            RaisePropertyChanged(() => SelectedComponent);
        }
    }
}
