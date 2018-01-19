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
    ///     ComponentsTreeViewModel class stores the logic & data of the ComponentsTreeView.
    ///     The main goal of the ComponentsTreeViewModel is to link between the data which related to the components dependency model
    ///     to the UI components.
    ///     This class inherits from Galasoft.MvvmLight.ViewModelBase which is the base class for any ViewModel in MVVM pattern.
    /// </summary>

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
            RaisePropertyChanged(() => Weight);
            RaisePropertyChanged(() => State);
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
