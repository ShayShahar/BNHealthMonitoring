#pragma once
#include "Node.h"
#include "CSVReader.h"

class Stx : public Node
{
	const float max_temperature = 85;
	const float min_temperature = -40;
	const float max_voltage = 12;
	const float min_voltage = 6;
	const float max_frequency = 2400;
	const float min_frequency = 2450;

private :

	float temperature;
	float voltage;
	float rf_frequency;
	CSVReader* m_reader;


public:
	Stx(string p_name);
	~Stx();
	void update_component_state() override;
};

