#pragma once
#include "Node.h"

class Sattelite : public Node
{
	enum State
	{
		HEALTHY,
		ACS,
		EPS,
		GPS
	};

public:
	Sattelite(string p_name, Node* p_parent);
	~Sattelite();

	void update_component_state() override;
};
