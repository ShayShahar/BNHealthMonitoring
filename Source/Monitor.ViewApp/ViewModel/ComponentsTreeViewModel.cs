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
    ///     ComponentsTreeViewModel class stores the logic & data of the ComponentsTreeView.
    ///     The main goal of the ComponentsTreeViewModel is to link between the data which related to the components dependency model
    ///     to the UI components.
    ///     This class inherits from Galasoft.MvvmLight.ViewModelBase which is the base class for any ViewModel in MVVM pattern.
    /// </summary>

    public class ComponentsTreeViewModel : ViewModelBase
    {
        private readonly DataState m_dataState;

        /// <summary>
        /// Initializes a new instance of the <see cref="ComponentsTreeViewModel"/> class.
        /// </summary>
        public ComponentsTreeViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_dataState.ComponentsUpdate.ObserveOnDispatcher().Subscribe(onComponentsUpdateEvent);
            m_dataState.SelectedComponentChangedEvent.ObserveOnDispatcher().Subscribe(onSelectionChanged);
        }

        /// <summary>
        /// Gets the components list from the DataState.
        /// </summary>
        public ObservableCollection<Component> Components
        {
            get { return m_dataState.Components; }
        }

        /// <summary>
        /// This function invokes where there is a change in the components' data in the DataState.
        /// </summary>
        private void onComponentsUpdateEvent(Unit p_unit)
        {
            RaisePropertyChanged(() => Components);
            RaisePropertyChanged(() => IsLoaded);
            RaisePropertyChanged(() => Weight);
            RaisePropertyChanged(() => State);
        }

        /// <summary>
        /// This function invokes where the user selects a component in the components tree.
        /// </summary>
        private void onSelectionChanged(Unit p_unit)
        {
            RaisePropertyChanged(() => Weight);
            RaisePropertyChanged(() => State);
            RaisePropertyChanged(() => IsComponentNotSelected);
        }

        /// <summary>
        /// Gets a value indicating whether the user selected any component.
        /// </summary>
        /// <value><c>true</c> if the user selected a component; otherwise, <c>false</c>.</value>
        public bool IsComponentNotSelected
        {
            get { return m_dataState.SelectedComponent == null; }
        }

        /// <summary>
        /// Gets the selected component's weight.
        /// </summary>
        public double? Weight
        {
            get { return m_dataState.SelectedComponent?.Weight; }
        }


        /// <summary>
        /// Gets the selected component's state.
        /// </summary>
        public string State
        {
            get { return m_dataState.SelectedComponent?.State; }
        }

        /// <summary>
        /// Gets a value indicating whether the health monitoring module data is loaded.
        /// </summary>
        /// <value><c>true</c> if this data is loaded; otherwise, <c>false</c>.</value>
        public bool IsLoaded
        {
            get { return Components.Count > 0; }
        }

    }
}
