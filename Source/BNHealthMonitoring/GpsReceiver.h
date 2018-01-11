#pragma once
#include "Node.h"
#include "CSVReader.h"

class GpsReceiver : public Node
{
private:
	enum State
	{
		HEALTHY,
		VOLTAGE_LOW,
		VOLTAGE_HIGH,
		SHOCK_HIGH,
		TEMPERATURE_LOW,
		TEMPERATURE_VERY_LOW,
		TEMPERATURE_HIGH,
		TEMPERATURE_VERY_HIGH,

	};


	/*
	GpsReceiver ranges:
	temp:	   ||ok: 1-70 ||low: -30 - 0||high: 71-80||very low: -40 - -31||very high: 81-85||
	shock: ||ok: 0-30||high:31-40||
	voltage: ||ok: 3.2 - 3.4||low: <3.3||high: >3.3||
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
	GpsReceiver(string p_name);
	~GpsReceiver();
	void update_component_state() override;
	void receive() override;
};

