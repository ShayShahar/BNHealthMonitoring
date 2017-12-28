using System;
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
        private static DataState s_dataState;

        private DataState()
        {
            m_componentsUpdated = new Subject<Unit>();

            m_components = new ObservableCollection<Component>();
            Component c = new Component
            {
                Name = "Sattelite Alpha",
                Children = new ObservableCollection<Component>
                {
                    new Component
                    {
                        Name = "GPS"
                    },
                    new Component
                    {
                        Name = "Magnometer"
                    }
                }
            };
            m_components.Add(c);
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
                    Children =  new ObservableCollection<Component>()
                };

                p_list.Add(component);
            }

            foreach (var c in p_component.LinksList)
            {
                addComponent(component.Children, c.Children);
            }
        }
    }
}
