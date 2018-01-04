#include "RWY.h"

RWY::RWY(string p_name) :Node(p_name)
{
	m_reader = new CSVReader("CSVFiles//RWY.csv");
}

RWY::~RWY()
{
	delete m_reader;
}

void RWY::update_component_state()
{
	vector<string> data = m_reader->readLine();

	temperature = stod(data[0]);
	voltage = stod(data[1]);
}
