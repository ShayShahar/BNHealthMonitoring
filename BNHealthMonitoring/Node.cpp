#include "Node.h"

Node::Node(string p_name)
{
	component_name = p_name;
	state = 0;
}

Node::~Node()
{
}

Node* Node::get_next()
{
	if (probabilities_table.find(state) == probabilities_table.end())
	{
		return nullptr;
	}

	list<Link> *lst = probabilities_table[state];
	double random = (rand() % 100) / 100;
	double begin = 0;
	double end = 0;

	for (list<Link>::iterator it = lst->begin(); it != lst->end(); ++it)
	{
		begin = end;
		end += begin + it->value;

		if (random > begin && random <= end)
		{
			return it->parent;
		}
	}

	return nullptr;
}

void Node::add_link(int p_state, Link p_link)
{
	if (probabilities_table.find(p_state) == probabilities_table.end())
	{
		list<Link>* lst = new list<Link>();
		lst->push_back(p_link);
		probabilities_table.insert_or_assign(p_state, lst);
	}
	else
	{
		probabilities_table[p_state]->push_back(p_link);
	}
}
