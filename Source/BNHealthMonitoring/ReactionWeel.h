#pragma once
#include "Node.h"
#include "CSVReader.h"

class ReactionWeel : public Node
{
	/*
	ReactionWeel ranges:
	temp:	   ||ok: 1-49 ||low: -19 - 0||high: 50-59||very low: -40 - -20||very high: 60 - 70|| 
	voltage: ||ok: 4-6||low: 3.4-3.9||high: 6.1-8||
	*/

private :
	const float max_temperature = 70;
	const float min_temperature = -40;
	const float max_voltage = 8;
	const float min_voltage = 3.4;

	float m_temperature;
	float m_voltage;

	CSVReader* m_reader;

public:
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

	ReactionWeel(string p_name);
	~ReactionWeel();
	void update_component_state() override;
	void receive() override;
};

