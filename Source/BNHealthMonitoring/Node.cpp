#include "Node.h"
#include "Utils.h"

void Node::propagate_state()
{
	if (m_state > 0)
		m_parent->notify(m_states[m_state].weight(), this);
}

void Node::add_dependency(Dependency p_dependency)
{
	m_dependencies->push_back(p_dependency);
}

void Node::add_parent(Node* p_parent)
{
	m_parent = p_parent;
}

list<Dependency>* Node::dependencies()
{
	return m_dependencies;
}

Node::Node(string p_name)
{
	m_dependencies = new list<Dependency>();
	m_name = p_name;
	m_state = 0;
	m_count = 0;
}

Node::~Node()
{
}

Node* Node::get_next()
{

	double rand = (double)(Utils::random() % 100) / 100;
	double begin = 0;
	double end = 0;

	for (list<Dependency>::iterator it = m_dependencies->begin(); it != m_dependencies->end(); ++it)
	{
		begin = end;
		end += begin + it->probability();

		if (rand > begin && rand <= end)
		{
			return it->child();
		}
	}

	return nullptr;
}

string Node::name()
{
	return m_name;
}

int Node::state()
{
	return m_state;
}

void Node::get_data(HealthMonitoringMessages::pComponent* p_msg)
{
	p_msg->set_name(m_name);

	if (m_dependencies->size() == 0)
		p_msg->set_state(get_state_str(m_state));

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
