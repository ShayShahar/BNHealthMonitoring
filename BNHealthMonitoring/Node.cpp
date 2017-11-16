#include "Node.h"

Node::Node(const char* p_name)
{
	component_name = strcopy(p_name);
	state = 0;
}

Node::~Node()
{
}

Node* Node::get_next()
{
	double random = (rand() % 100) / 100;
	double begin = 0;
	double end = 0;

	LinkedList<Link*> prob_list = probabilities_list[state];
	ListItem<Link*> current = prob_list.first();
	
	while(current != prob_list.end())
	{
		begin = end;
		end += begin + current.value->value;

		if (random > begin && random <= end)
		{
			return current.value->parent;
		}

		current = *(current.next);
	}

	return nullptr;
}

void Node::add_link(int p_state, Link p_link)
{
	//if (probabilities_table.find(p_state) == probabilities_table.end())
	//{
	//	list<Link>* lst = new list<Link>();
	//	lst->push_back(p_link);
	//	probabilities_table.insert_or_assign(p_state, lst);
	//}
	//else
	//{
	//	probabilities_table[p_state]->push_back(p_link);
	//}
}
