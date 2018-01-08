#pragma once
#include "Node.h"
#include "CommunicationHandler.h"
#include "CSVReader.h"

class Gps : public Node
{
public:

	Gps(string p_name);
	~Gps();

	void update_component_state() override;
	string get_state_str(int p_state) override;
};

