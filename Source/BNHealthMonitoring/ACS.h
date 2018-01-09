#pragma once
#include "Node.h"
#include "CSVReader.h"

class ACS : public Node
{
private:
	float m_voltage;
	CSVReader* m_reader;
	const float max_voltage = 12.0;

public:
	ACS(string p_name);
	~ACS();
	void update_component_state() override;
	void receive() override;
};

