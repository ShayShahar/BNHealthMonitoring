#pragma once
#include "Node.h"

class ComponentsModel
{
public:
	ComponentsModel(Node*);
	~ComponentsModel();
	Node* find_fault();

	Node* system_root;

};

