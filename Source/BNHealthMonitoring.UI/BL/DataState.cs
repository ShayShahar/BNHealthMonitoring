﻿using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Reactive;
using System.Reactive.Subjects;
using BNHealthMonitoring.UI.Model;
using HealthMonitoringMessages;

namespace BNHealthMonitoring.UI.BL
{
    public class DataState
    {
        private ObservableCollection<Component> m_components;
        private readonly ISubject<Unit> m_componentsUpdated;
        private readonly ISubject<Tuple<int, double>> m_locationUpdate;
        private static DataState s_dataState;
        private readonly ISubject<Unit> m_selectedComponentChanged;
        private Component m_selectedComponent;
        private double m_px;
        private double m_py;
        private double m_pz;

        private DataState()
        {
            m_locationUpdate = new Subject<Tuple<int, double>>();
            m_componentsUpdated = new Subject<Unit>();
            m_selectedComponentChanged = new Subject<Unit>();
            m_components = new ObservableCollection<Component>();

            m_px = 0;
            m_py = 0;
            m_pz = 0;
        }

        public static DataState GetInstance()
        {
            if (s_dataState == null)
                s_dataState = new DataState();

            return s_dataState;
        }

        public IObservable<Unit> ComponentsUpdate
        {
            get { return m_componentsUpdated; }
        }

        public IObservable<Unit> SelectedComponentChangedEvent
        {
            get { return m_selectedComponentChanged; }
        }
        public IObservable<Tuple<int, double>> LocationUpdated
        {
            get { return m_locationUpdate; }
        }

        public ObservableCollection<Component> Components
        {
            get
            {
                return m_components;
            }
            set
            {
                if (value.SequenceEqual(m_components))
                    return;

                m_components = value;
                m_componentsUpdated.OnNext(new Unit());
            }
        }

        public Component SelectedComponent
        {
            get { return m_selectedComponent; }
            set
            {
                if (m_selectedComponent != null && m_selectedComponent.Equals(value))
                {
                    return;
                }

                m_selectedComponent = value;
                m_selectedComponentChanged.OnNext(new Unit());
            }
        }

        public void SetComponents(CDMMessage p_components)
        {
            ObservableCollection<Component> components = new ObservableCollection<Component>();
            addComponent(components, p_components.CdmRoot);
            Components = components;
        }

        private void addComponent(ObservableCollection<Component> p_list, pComponent p_component)
        {
            var component = p_list.FirstOrDefault(p_c => p_component.Name.Equals(p_c.Name, StringComparison.InvariantCultureIgnoreCase));

            if (component == null)
            {
                component = new Component
                {
                    Name = p_component.Name,
                    State = p_component.State,
                    Children = new ObservableCollection<Component>()
                };

                p_list.Add(component);

                foreach (var c in p_component.LinksList)
                {
                    component.Links.Add(new Link
                    {
                        DestenationName = c.Children.Name,
                        State = c.State,
                        Probability = c.Probability
                    });

                    addComponent(component.Children, c.Children);
                }
            }
        }

        public void UpdateLocation(LocationMessage p_location)
        {
            if (m_px == m_py && m_py == m_pz && m_pz == 0)
            {
                m_px = p_location.X;
                m_py = p_location.Y;
                m_pz = p_location.Z;

                return;
            }

            double delta =
                Math.Sqrt(Math.Pow(p_location.X - m_px, 2) 
                          + Math.Pow(p_location.Y - m_py, 2) 
                          + Math.Pow(p_location.Z - m_pz, 2));

            m_locationUpdate.OnNext(new Tuple<int, double>(p_location.Seconds, delta));

            m_px = p_location.X;
            m_py = p_location.Y;
            m_pz = p_location.Z;
        }
    }
}
