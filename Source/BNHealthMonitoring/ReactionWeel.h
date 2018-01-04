#pragma once
#include "Node.h"
#include "CSVReader.h"

class ReactionWeel : public Node
{
	enum State
	{
		HEALTHY,
		TEMPREATURE,
		VOLTAGE
	};

	const float max_temperature = 70;
	const float min_temperature = -40;
	const float max_voltage = 8;
	const float min_voltage = 3.4;

private :

	float m_temperature;
	float m_voltage;

	CSVReader* m_reader;

public:
	ReactionWeel(string p_name, Node* p_parent);
	~ReactionWeel();
	void update_component_state() override;
};

