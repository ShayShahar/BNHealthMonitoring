#pragma once
#include "Node.h"

class GenericComp : public Node
{
public:
	GenericComp(string p_name, Node* p_parent);
	~GenericComp();

	void update_component_state() override;
};

