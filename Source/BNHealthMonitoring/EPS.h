#pragma once
#include "Node.h"
#include "CSVReader.h"

class EPS : public Node
{
private:
	enum State
	{
		HEALTHY,
		TEMPERATURE,
		VOLTAGE
	};

	const float max_temperature = 60;
	const float min_temperature = -20;
	const float max_voltage = 4.2;
	const float min_voltage = 3;

	float m_temperature;
	float m_voltage;

	CSVReader* m_reader;

public:
	EPS(string p_name, Node* p_parent);
	~EPS();
	void update_component_state() override;
};
