#pragma once
#include "Node.h"

class CGps : public Node
{
public:
	CGps(string p_name);
	~CGps();

	void update_component_state(int* p_signals) override;
};

