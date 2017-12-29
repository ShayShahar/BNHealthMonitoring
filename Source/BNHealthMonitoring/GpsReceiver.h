#pragma once
#include "Node.h"
#include "CSVReader.h"

class GpsReceiver : public Node
{
	const float max_temperature = 85; //celsius
	const float min_temperature = -40; //celsius
	const float max_shock = 40; //grams
	const float max_volatage = 3.3; // volt

private:
	float temperature;
	float shock;
	float voltage;

	CSVReader* m_reader;

public:
	GpsReceiver(string p_name);
	~GpsReceiver();
	void update_component_state() override;
};

