#pragma once
#include "Node.h"
#include "CSVReader.h"

class EPS : public Node
{
private:
	const float max_temperature = 60;
	const float min_temperature = -20;
	const float max_voltage = 4.2;
	const float min_voltage = 3;

	float m_temperature;
	float m_voltage;

	CSVReader* m_reader;

public:
	EPS(string p_name);
	~EPS();
	void update_component_state() override;
	string get_state_str(int p_state) override;

	enum State
	{
		HEALTHY,
		TEMPERATURE,
		VOLTAGE
	};

};

