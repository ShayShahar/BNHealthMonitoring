#pragma once
#include "Component.h"
#include "CSVReader.h"

class ACS : public Component
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

