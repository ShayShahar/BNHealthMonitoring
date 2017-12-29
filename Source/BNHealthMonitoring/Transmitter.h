#pragma once
#include "Node.h"
#include "CSVReader.h"

class Transmitter : public Node
{
	const float max_temperature = 80;
	const float min_temperature = -40;
	const float max_voltage = 3.5;
	const float min_voltage = 3.2;
	const float max_frequency = 440;
	const float min_frequency = 430;

private:

	float temperature;
	float voltage;
	float frequency;

	CSVReader* m_reader;


public:
	Transmitter(string p_name);
	~Transmitter();
	void update_component_state() override;
};

