#pragma once

#include "Link.h"
#include "LinkedList.h"
#include "Utils.h"

class Node
{
private:
	int state;
	char* component_name;
	LinkedList<Link>* probabilities_list;
	unsigned int nStates;

public:
	Node(const char* p_name, unsigned int p_nStates);
	virtual ~Node();
	Node* get_next() const;
	void add_link(unsigned int p_state, Link p_link);
	char* name();

	//generate evidence from signals and set the update the link probabilities for each component
	virtual void update_component_state(char* p_signals) = 0;
};