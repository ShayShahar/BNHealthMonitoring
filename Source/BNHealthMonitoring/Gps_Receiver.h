#pragma once
#include "Node.h"
#include "CSVReader.h"

const float max_temperature = 85;
const float min_temperature = -40;

const float max_vibration = 30;
const float max_volatage = 3.3;


class Gps_Receiver : public Node
{
	float temperature;
	float vibration;
	float voltage;


	CSVReader* m_reader;




public:
	Gps_Receiver(const char* p_name, unsigned int p_nStates);
	~Gps_Receiver();
	void update_component_state() override;

};

