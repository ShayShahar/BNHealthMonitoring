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
	vector<string> data = m_reader->readLine();

	m_temperature = stod(data[0]);
	m_vibration = stod(data[1]);
	m_altitude = stod(data[2]);

	if ((1 < m_temperature < 60) && (0 < m_vibration < 25) && (0 < m_altitude < 60000))
	{
		m_state = State::HEALTHY;
	}
	else if (-29 < m_temperature < 0)
	{
		m_state = State::TEMPERATURE_LOW;
	}
	else if (-55 < m_temperature < -30)
	{
		m_state = State::TEMPERATURE_VERY_LOW;
	}
	else if (61 < m_temperature < 74)
	{
		m_state = State::TEMPERATURE_HIGH;
	}
	else if (75 < m_temperature < 85)
	{
		m_state = State::TEMPERATURE_VERY_HIGH;
	}
	else if (26 < m_vibration < 30)
	{
		m_state = State::VIBRATION_HIGH;
	}
	else if (60001 < m_altitude < 70000)
	{
		m_state = State::ALTITUDE_HIGH;
	}


}

void GpsAntenna::receive()
{
}
