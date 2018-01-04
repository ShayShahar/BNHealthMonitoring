#pragma once
#include "Node.h"
#include "CSVReader.h"

class Magnetorquer : public Node
{
private:
	const float max_temperature = 75.0;
	const float min_temperature = -30.0;
	const float max_voltage = 5.0;

	float m_temperature;
	float m_voltage;
	CSVReader* m_reader;

public:
	enum State
	{
		HEALTHY,
		TEMPERATURE,
		VOLTAGE
	};


	Magnetorquer(string p_name, Node* p_parent);
	~Magnetorquer();

	void update_component_state() override;
	string get_state_str(int p_state) override;
};

