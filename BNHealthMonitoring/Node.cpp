#include "Node.h"

Node::Node(const char* p_name, unsigned int p_nStates)
{
	probabilities_list = new LinkedList<Link>[p_nStates];
	component_name = strcopy(p_name);
	state = 0;
	nStates = p_nStates;

}

Node::~Node()
{
}

Node* Node::get_next() const
{
	double rand = (double)(random() % 100) / 100;
	double begin = 0;
	double end = 0;

	LinkedList<Link> prob_list = probabilities_list[state];
	if (prob_list.size == 0)
		return nullptr;

	ListItem<Link> current = prob_list.first();
	
	while(current != prob_list.end())
	{
		begin = end;
		end += begin + current.value.value;

		if (rand > begin && rand <= end)
		{
			return current.value.parent;
		}

		current = *(current.next);

		if (current == prob_list.end())
			return current.value.parent;

	}

	return nullptr;
}

void Node::add_link(unsigned int p_state, Link p_link)
{
	if (p_state >= nStates)
		return;
	
	probabilities_list[p_state].add(p_link);
}

char * Node::name()
{
	return component_name;
}
