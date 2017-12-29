#pragma once
#include "Node.h"
#include "CSVReader.h"

class Gps_Ant : public Node
{
	//antenna properties:
	const float max_temperature = 85;
	const float min_temperature = -55;
	const float max_vibration = 30;
	const float max_altitude = 70000;

private:

	CSVReader* m_reader;
	float tempature;
	float vibration;
	float altitude;

public:
	Gps_Ant(string p_name);
	~Gps_Ant();
	void update_component_state() override;
};

