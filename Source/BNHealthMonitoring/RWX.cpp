#include "RWX.h"

RWX::RWX(string p_name):Node(p_name)
{
	m_reader = new CSVReader("CSVFiles//RWX.csv");
}

RWX::~RWX()
{
	delete m_reader;
}

void RWX::update_component_state()
{
	vector<string> data = m_reader->readLine();

	temperature = stod(data[0]);
	voltage = stod(data[1]);
}
