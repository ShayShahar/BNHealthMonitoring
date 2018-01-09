#pragma once
#include "Node.h"
#include "CSVReader.h"

class Magnetorquer : public Node
{
	/*
	Magnetorquer ranges:
	temp:	   ||ok: 1-50 ||low: -20 - 0||high: 51-64||very low: -30 - -20||very high:65 - 75||
	voltage: ||ok: 5||low: <5||high: >%5||
	*/

private:	
	enum State
	{
		HEALTHY,
		TEMPERATURE_HIGH,
		TEMPERATURE_VERY_HIGH,
		TEMPERATURE_LOW,
		TEMPERATURE_VERY_LOW,
		VOLTAGE_LOW,
		VOLTAGE_HIGH
	};

	const float max_temperature = 75.0;
	const float min_temperature = -30.0;
	const float max_voltage = 5.0;

	float m_temperature;
	float m_voltage;
	CSVReader* m_reader;

public:


	Magnetorquer(string p_name);
	~Magnetorquer();

	void update_component_state() override;
	void receive() override;

};

