#pragma once
#include "Node.h"
#include "CSVReader.h"

class GpsReceiver : public Node
{
private:

	/* Ranges:
		-Temperature:
			*Ok : 20 - 65
			*Hot : 66 - 75 || -20 - 19
			*Critical : 76 - 84 ||-39 - -21
	*/

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

	GpsReceiver(string p_name);
	~GpsReceiver();
	void update_component_state() override;
	string get_state_str(int p_state) override;

};

