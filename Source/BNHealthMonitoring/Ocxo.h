#pragma once
#include "Node.h"
#include "CSVReader.h"

class Ocxo : public Node
{
	const float max_temperature = 70.0;
	const float min_temperature = -30.0;
	const float max_voltage = 5.25;
	const float min_voltage = 4.75;
	const float max_frequency = 100.0;
	const float min_frequency = 8.0;

private:

	float temperature;
	float voltage;
	float frequency;

	CSVReader* m_reader;



public:
	Ocxo(string p_name);
	~Ocxo();
	void update_component_state() override;
};

