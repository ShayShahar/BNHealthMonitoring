#include "GpsReceiver.h"

GpsReceiver::GpsReceiver(string p_name) : Node(p_name), m_temperature(0), m_shock(0), m_voltage(0)
{
	m_reader = new CSVReader("CSVFiles//GpsReceiver.csv");

	//example 
	m_states.insert({ State::HEALTHY, StateData(-0.5, "Healthy") });
	m_states.insert({ State::TEMPERATURE_HIGH, StateData(1, "Temperature High") });
	m_states.insert({ State::TEMPERATURE_VERY_HIGH, StateData(2, "Temperature Very High") });
	m_states.insert({ State::SHOCK, StateData(1.3, "Shock") });

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
