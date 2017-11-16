#pragma once
#include "Node.h"

class CGps : public Node
{
public:
	CGps(const char* p_name, unsigned int p_nStates);
	~CGps();

	void update_component_state(char* p_signals) override;
};

