#include "Stx.h"

Stx::Stx(string p_name) : Node(p_name)
{
	m_reader = new CSVReader("CSVFiles//Receiver.csv");
}


Stx::~Stx()
{
	delete m_reader;
}

void Stx::update_component_state()
{
	vector<string> data = m_reader->readLine();

	temperature = stod(data[0]);
	voltage = stod(data[1]);
	rf_frequency = stod(data[2]);

}
