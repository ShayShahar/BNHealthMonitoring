#pragma once
#include "Node.h"
#include "CSVReader.h"

class GpsAntenna : public Node
{
private:
	enum State
	{
		HEALTHY,
		TEMPERATURE,
		VIBRATION,
		ALTITUDE
	};

	//antenna properties:
	const float max_temperature = 85;
	const float min_temperature = -55;
	const float max_vibration = 30;
	const float max_altitude = 70000;

	CSVReader* m_reader;

	float m_tempature;
	float m_vibration;
	float m_altitude;

public:
	GpsAntenna(string p_name, Node* p_parent);
	~GpsAntenna();
	void update_component_state() override;
};
