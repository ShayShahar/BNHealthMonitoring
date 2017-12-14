#pragma once
#include "Node.h"

class GenericComp : public Node
{
public:
	GenericComp(const char* p_name, unsigned int p_nStates);
	~GenericComp();

	void update_component_state(char* p_signals) override;
};

