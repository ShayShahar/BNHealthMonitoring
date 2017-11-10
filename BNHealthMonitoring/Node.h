#pragma once

#include "Link.h"
#include "LinkedList.h"
#include "Utils.h"

class Node
{
private:
	int state;
	char* component_name;
	LinkedList<Link*> probabilities_list;

public:
	Node(const char* p_name);
	virtual ~Node();
	Node* get_next();
	void add_link(int p_state, Link p_link);

	//generate evidence from signals and set the update the link probabilities for each component
	virtual void update_component_state(char* p_signals) = 0;
};

