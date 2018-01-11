#pragma once
#include "Node.h"
#include "CSVReader.h"

class EPS : public Node
{
	/*
	EPS ranges:
	temp:	   ||ok: 1-39 ||low: -10 - 0||high: 40-50||very low: -20 - -11||very high: 51 - 60||
	voltage: ||ok: 3.1-4.2||low: <3||high: >4.2||
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

	const float max_temperature = 60;
	const float min_temperature = -20;
	const float max_voltage = 4.2;
	const float min_voltage = 3;

	float m_temperature;
	float m_voltage;

	CSVReader* m_reader;

public:
	EPS(string p_name);
	~EPS();
	void update_component_state() override;
	void receive() override;
};

