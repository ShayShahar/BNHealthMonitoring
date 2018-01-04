#include "RWZ.h"

RWZ::RWZ(string p_name) :Node(p_name)
{
	m_reader = new CSVReader("CSVFiles//RWZ.csv");
}

RWZ::~RWZ()
{
	delete m_reader;
}

void RWZ::update_component_state()
{
	vector<string> data = m_reader->readLine();

	temperature = stod(data[0]);
	voltage = stod(data[1]);
}
