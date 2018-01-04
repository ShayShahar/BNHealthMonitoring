#pragma once
#include "Node.h"

class Sattelite : public Node
{
public:
	enum State
	{
		HEALTHY,
		ACS,
		EPS,
		GPS
	};

	Sattelite(string p_name, Node* p_parent);
	~Sattelite();

	void update_component_state() override;
	string get_state_str(int p_state) override;
};
