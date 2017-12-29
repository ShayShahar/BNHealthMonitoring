#include "Receiver.h"

Receiver::Receiver(string p_name) : Node(p_name)
{
	m_reader = new CSVReader("CSVFiles//Receiver.csv");
}

Receiver::~Receiver()
{
	delete m_reader;
}

void Receiver::update_component_state()
{
	vector<string> data = m_reader->readLine();

	temperature = stod(data[0]);
	voltage = stod(data[1]);
	frequency = stod(data[2]);
}
