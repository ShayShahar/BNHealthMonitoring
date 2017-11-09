#pragma once

#include <list>
#include <map>
#include "Link.h"

using namespace std;

class Node
{
private:
	//TODO: implement fuzzier for each component
	virtual  void fuzzier() = 0;
	int state;

public:
	Node(string p_name);
	virtual ~Node();
	Node* get_next();
	void add_link(int p_state, Link p_link);

	//todo:: generate evidence from signals
	virtual void update_component_state(int* p_signals) = 0;

	map<int, list<Link>*> probabilities_table;
	string component_name;
};

