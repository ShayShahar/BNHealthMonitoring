#include "EPS.h"

EPS::EPS(string p_name, Node* p_parent) : Node(p_name, p_parent)
{
	m_reader = new CSVReader("CSVFiles//EPS.csv");
}

EPS::~EPS()
{
	delete m_reader;
}

void EPS::update_component_state()
{
	vector<string> data = m_reader->readLine();

	m_temperature = stod(data[0]);
	m_voltage = stod(data[1]);
}
