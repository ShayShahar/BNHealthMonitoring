#pragma once
#include "Node.h"
#include "CSVReader.h"

class ReactionWeel : public Node
{
private :
	const float max_temperature = 70;
	const float min_temperature = -40;
	const float max_voltage = 8;
	const float min_voltage = 3.4;

	float m_temperature;
	float m_voltage;

	CSVReader* m_reader;

	void notify(int p_state, Node* p_sender) override;

public:
	enum State
	{
		HEALTHY,
		TEMPERATURE,
		VOLTAGE
	};

	ReactionWeel(string p_name);
	~ReactionWeel();
	void update_component_state() override;
	string get_state_str(int p_state) override;
};

