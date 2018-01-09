#include "ACS.h"

ACS::ACS(string p_name) : Node(p_name), m_voltage(0)
{
	m_reader = new CSVReader("CSVFiles//ACS.csv");
}

ACS::~ACS()
{
	delete m_reader;
}
void ACS::update_component_state()
{
	vector<string> data = m_reader->readLine();

	m_voltage = stod(data[0]);

}

void ACS::receive()
{
}

