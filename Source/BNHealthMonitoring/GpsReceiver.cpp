#include "GpsReceiver.h"

GpsReceiver::GpsReceiver(string p_name, Node* p_parent) : Node(p_name, p_parent), m_temperature(0), m_shock(0), m_voltage(0)
{
	m_reader = new CSVReader("CSVFiles//GpsReceiver.csv");
}

GpsReceiver::~GpsReceiver()
{
	delete m_reader;
}

void GpsReceiver::update_component_state()
{
	vector<string> data = m_reader->readLine();

	m_temperature = stod(data[0]);
	m_shock = stod(data[1]);
	m_voltage = stod(data[2]);
}

string GpsReceiver::get_state_str(int p_state)
{
	switch (p_state)
	{
		case State::VOLTAGE:
			return "VOLTAGE";
		case State::TEMPERATURE:
			return "TEMPERATURE";	
		case State::SHOCK:
			return "SHOCK";
	}

	return "HEALTHY";
}
