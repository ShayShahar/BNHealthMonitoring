#pragma once
#include "Node.h"
#include "CSVReader.h"

// VHF & UHF Transceiver
// divide for 2 componnets: (1)Transmitter (2)Receiver

class Transceiver : public Node
{
	const float max_temperature = 80;
	const float min_temperature = -40;

private:
	float temperature;
	CSVReader* m_reader;
	
public:
	Transceiver(string p_name);
	~Transceiver();
	void update_component_state() override;
};

