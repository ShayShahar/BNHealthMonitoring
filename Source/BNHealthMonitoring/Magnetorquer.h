#pragma once
#include "Node.h"
#include "CSVReader.h"

class Magnetorquer : public Node
{

	const float max_temperature = 75.0;
	const float min_temperature = -30.0;
	const float max_voltage = 5.0;

private:

	float temperature;
	float voltage;
	CSVReader* m_reader;



public:
	Magnetorquer(string p_name);
	~Magnetorquer();

	void update_component_state() override;
};

