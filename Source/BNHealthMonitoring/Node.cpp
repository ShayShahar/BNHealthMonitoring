#include "Node.h"

Node::Node(string p_name, Node* p_parent)
{
	m_parent = p_parent;
	m_name = p_name;
	m_state = 0;
}

Node::~Node()
{
}

Node* Node::get_next()
{
	if (m_probabilities.find(m_state) == m_probabilities.end())
	{
		return nullptr;
	}

	list<Link> *lst = m_probabilities.at(m_state);
	double rand = (double)(Utils::random() % 100) / 100;
	double begin = 0;
	double end = 0;

	for (list<Link>::iterator it = lst->begin(); it != lst->end(); ++it)
	{
		begin = end;
		end += begin + it->value;

		if (rand > begin && rand <= end)
		{
			return it->parent;
		}
	}

	return nullptr;
}

void Node::add_link(unsigned int p_state, Link p_link)
{
	if (m_probabilities.find(p_state) == m_probabilities.end())
	{
		list<Link>* lst = new list<Link>();
		lst->push_back(p_link);
		m_probabilities.insert({p_state, lst});
	}
	else
	{
		m_probabilities[p_state]->push_back(p_link);
	}
}

string Node::name()
{
	return m_name;
}

map<int, list<Link>*> Node::links()
{
	return m_probabilities;
}

int Node::state()
{
	return m_state;
}

void Node::get_data(HealthMonitoringMessages::pComponent* p_msg)
{
	p_msg->set_name(m_name);
	p_msg->set_state(m_state);

	for (map<int, list<Link>*>::iterator it = m_probabilities.begin(); it != m_probabilities.end(); ++it)
	{		
		for (list<Link>::iterator lt = it->second->begin(); lt != it->second->end(); ++lt)
		{
			HealthMonitoringMessages::pLink* links = p_msg->add_links();

			links->set_state(it->first);
			links->set_probability(lt->value);
			
			if (lt->parent == nullptr)
				continue;

			HealthMonitoringMessages::pComponent *parent = links->mutable_children();
			lt->parent->get_data(parent);
		}			
	}
}
