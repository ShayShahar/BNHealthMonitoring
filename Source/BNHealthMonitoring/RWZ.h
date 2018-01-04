#pragma once
#include "Node.h"
#include "CSVReader.h"

class RWZ : public Node
{
	const float max_temperature = 70;
	const float min_temperature = -40;
	const float max_voltage = 8;
	const float min_voltage = 3.4;

private:

	float temperature;
	float voltage;

	CSVReader* m_reader;

public:
	RWZ(string p_name);
	~RWZ();
	void update_component_state() override;
};

