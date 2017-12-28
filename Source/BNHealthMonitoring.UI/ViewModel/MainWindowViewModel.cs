﻿using System;
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
    public class MainWindowViewModel : ViewModelBase
    {
        private readonly MessageService m_messageService;
        private readonly DataState m_dataState;

        public MainWindowViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_messageService = MessageService.GetInsatnce();
            m_dataState.ComponentsUpdate.ObserveOnDispatcher().Subscribe(onComponentsUpdateEvent);
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
