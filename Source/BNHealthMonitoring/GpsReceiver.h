#pragma once
#include "Node.h"
#include "CSVReader.h"

class GpsReceiver : public Node
{
private:
	const float max_temperature = 85; //celsius
	const float min_temperature = -40; //celsius
	const float max_shock = 40; //grams
	const float max_volatage = 3.3; // volt

	float m_temperature;
	float m_shock;
	float m_voltage;

	CSVReader* m_reader;

public:
	enum State
	{
		HEALTHY,
		TEMPERATURE,
		VOLTAGE,
		SHOCK
	};

	GpsReceiver(string p_name, Node* p_parent);
	~GpsReceiver();
	void update_component_state() override;
	string get_state_str(int p_state) override;

};

