#include "Component.h"
#include "Utils.h"

void Component::propagate_state()
{
	if (m_states.find(m_state) != m_states.end())
	{
		m_weight += m_states[m_state].weight();

		if (m_weight > 20)
			m_weight = 20;

		if (m_weight < 1)
			m_weight = 1;

		m_parent->notify();
	}
}

void Component::add_dependency(Dependency p_dependency)
{
	m_dependencies->push_back(p_dependency);
}

void Component::add_parent(Component* p_parent)
{
	m_parent = p_parent;
}

list<Dependency>* Component::dependencies()
{
	return m_dependencies;
}

double Component::weight()
{
	return m_weight;
}

void Component::notify()
{
	double weight = 0;

	for (list<Dependency>::iterator it = m_dependencies->begin(); it != m_dependencies->end(); ++it)
	{
		weight += it->child()->weight();
	}

	for (list<Dependency>::iterator it = m_dependencies->begin(); it != m_dependencies->end(); ++it)
	{
		it->set_probability(it->child()->weight() / weight);
	}

	//normalize node's weight
	m_weight = weight / m_dependencies->size();

	if (m_parent != nullptr)
		m_parent->notify();
}

map<int, StateData> Component::states()
{
	return m_states;
}

Component::Component(string p_name)
{
	m_dependencies = new list<Dependency>();
	m_name = p_name;
	m_state = 0;
	m_weight = 1;
}

Component::~Component()
{
}

Component* Component::get_next()
{
	double rand = (double)(Utils::random() % 101) / 100;
	double begin = 0;
	double end = 0;

	for (list<Dependency>::iterator it = m_dependencies->begin(); it != m_dependencies->end(); ++it)
	{
		begin = end;
		end = begin + it->probability();

		if (rand >= begin && rand <= end || it->child() == m_dependencies->back().child())
		{
			return it->child();
		}
	}

	return nullptr;
}

string Component::name()
{
	return m_name;
}

int Component::state()
{
	return m_state;
}

void Component::get_data(HealthMonitoringMessages::pComponent* p_msg)
{
	p_msg->set_name(m_name);

	if (m_dependencies->size() == 0)
		p_msg->set_state(m_states[m_state].name());

	p_msg->set_weight(m_weight);

	for (list<Dependency>::iterator it = m_dependencies->begin(); it != m_dependencies->end(); ++it)
	{
		HealthMonitoringMessages::pLink* links = p_msg->add_links();

		links->set_probability(it->probability());

		if (it->child() == nullptr)
			continue;

		HealthMonitoringMessages::pComponent *parent = links->mutable_children();
		it->child()->get_data(parent);
	}
}
