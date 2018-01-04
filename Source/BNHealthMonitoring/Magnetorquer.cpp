#include "Magnetorquer.h"


Magnetorquer::Magnetorquer(string p_name, Node* p_parent) : Node(p_name, p_parent), m_temperature(0), m_voltage(0)
{
	m_reader = new CSVReader("CSVFiles//Magnetorquer.csv");
}

Magnetorquer::~Magnetorquer()
{
	delete m_reader;
}

void Magnetorquer::update_component_state()
{
	vector<string> data = m_reader->readLine();

	m_temperature = stod(data[0]);
	m_voltage = stod(data[1]);
}

string Magnetorquer::get_state_str(int p_state)
{
	switch (p_state)
	{
		case State::VOLTAGE:
			return "VOLTAGE";
		case State::TEMPERATURE:
			return "TEMPERATURE";
	}

	return "HEALTHY";
}
