#pragma once
#include "Node.h"
#include "CSVReader.h"

class ACS : public Node
{
	const float max_voltage = 12.0;

private:

	float voltage;
	CSVReader* m_reader;


public:
	ACS(string p_name);
	~ACS();
	void update_component_state() override;
};

