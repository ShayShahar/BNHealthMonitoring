#pragma once
#include "Node.h"
#include "CSVReader.h"

class Magnetorquer : public Node
{
	/*
	Magnetorquer ranges:
	temp:	   ||ok: 1-60 ||low: -30 - 0||high: 61-75||
	voltage: ||ok: 5||low: <5||high: >%5||
	*/

private:	
	enum State
	{
		HEALTHY,
		TEMPERATURE,
		VOLTAGE
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

