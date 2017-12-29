#include "Transceiver.h"


Transceiver::Transceiver(string p_name) : Node(p_name)
{
	m_reader = new CSVReader("CSVFiles//Transceiver.csv");
}

Transceiver::~Transceiver()
{
	delete m_reader;
}

void Transceiver::update_component_state()
{
	vector<string> data = m_reader->readLine();

	temperature = stod(data[0]);
}
