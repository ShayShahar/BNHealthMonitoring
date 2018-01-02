#include "Ocxo.h"


Ocxo::Ocxo(string p_name) : Node(p_name)
{
	m_reader = new CSVReader("CSVFiles//Ocxo.csv");
}

Ocxo::~Ocxo()
{
	delete m_reader;
}
void Ocxo::update_component_state()
{
	vector<string> data = m_reader->readLine();

	temperature = stod(data[0]);
	voltage = stod(data[1]);
	frequency = stod(data[2]);

}
