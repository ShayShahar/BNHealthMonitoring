#include "Transmitter.h"


Transmitter::Transmitter(string p_name) : Node(p_name)
{
	m_reader = new CSVReader("CSVFiles//Receiver.csv");
}


Transmitter::~Transmitter()
{
	delete m_reader;
}

void Transmitter::update_component_state()
{
	vector<string> data = m_reader->readLine();

	temperature = stod(data[0]);
	voltage = stod(data[1]);
	frequency = stod(data[2]);

}
