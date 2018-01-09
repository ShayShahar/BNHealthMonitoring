#include "GpsAntenna.h"

GpsAntenna::GpsAntenna(string p_name) : Node(p_name), m_temperature(0), m_vibration(0), m_altitude(0)
{
	m_reader = new CSVReader("CSVFiles//Gps_Ant.csv");

	m_states.insert({ State::HEALTHY, StateData(-0.5, "Healthy") });
	m_states.insert({ State::TEMPERATURE_HIGH, StateData(1, "Temperature High") });
	m_states.insert({ State::TEMPERATURE_LOW, StateData(1, "Temperature Low") });
	m_states.insert({ State::TEMPERATURE_VERY_LOW, StateData(2, "Temperature Very Low") });
	m_states.insert({ State::TEMPERATURE_VERY_HIGH, StateData(2, "Temperature Very High") });
	m_states.insert({ State::VIBRATION_HIGH, StateData(1.3, "Vibration High") });
	m_states.insert({ State::ALTITUDE_HIGH, StateData(1, "Altitude High") });
}

GpsAntenna::~GpsAntenna()
{
	delete m_reader;
}



void GpsAntenna::update_component_state()
{

	if ((m_temperature > -29) && (m_temperature < 0))
	{
		m_state = State::TEMPERATURE_LOW;
		return;
	}
	if ((m_temperature > -55) && (m_temperature < -30))
	{
		m_state = State::TEMPERATURE_VERY_LOW;
		return;
	}
	if ((m_temperature > 61) && (m_temperature < 74))
	{
		m_state = State::TEMPERATURE_HIGH;
		return;
	}
	if ((m_temperature > 75) && (m_temperature < 85))
	{
		m_state = State::TEMPERATURE_VERY_HIGH;
		return;
	}
	if ((m_vibration > 26) && (m_vibration < 30))
	{
		m_state = State::VIBRATION_HIGH;
		return;
	}
	if ((m_altitude > 60001) && (m_altitude < 70000))
	{
		m_state = State::ALTITUDE_HIGH;
		return;
	}
	
		m_state = State::HEALTHY;

}
void GpsAntenna::receive()
{
	vector<string> data = m_reader->readLine();

	m_temperature = stod(data[0]);
	m_vibration = stod(data[1]);
	m_altitude = stod(data[2]);
}
