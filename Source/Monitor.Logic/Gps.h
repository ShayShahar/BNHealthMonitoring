#pragma once
#include "Component.h"
#include "CommunicationHandler.h"
#include "CSVReader.h"

class Gps : public Component
{
public:

	Gps(string p_name);
	~Gps();

	void update_component_state() override;
	void receive() override;
};

