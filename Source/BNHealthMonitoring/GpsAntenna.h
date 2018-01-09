#pragma once
#include "Node.h"
#include "CSVReader.h"

class GpsAntenna : public Node
{
	/*
	antenna ranges:
	temp:	   ||ok: 1-60 ||low: -29 - 0||high: 61-74||very low: -55 - -30||very high: 75 - 85
	vibration: ||ok: 0-25||high:26-30||
	alttitude: ||ok: 0-60,000||high: 60,001-70,000||
	*/
private:
	enum State
	{
		HEALTHY,
		TEMPERATURE_HIGH,
		TEMPERATURE_VERY_HIGH,
		TEMPERATURE_LOW,
		TEMPERATURE_VERY_LOW,
		VIBRATION_HIGH,
		ALTITUDE_HIGH
	};

	//antenna properties:
	const float max_temperature = 85;
	const float min_temperature = -55;
	const float max_vibration = 30;
	const float max_altitude = 70000;

	CSVReader* m_reader;

	float m_temperature;
	float m_vibration;
	float m_altitude;

public:
	GpsAntenna(string p_name);
	~GpsAntenna();
	void update_component_state() override;
	void receive() override;
};

