#include "Magnetorquer.h"

Magnetorquer::Magnetorquer(string p_name) : Component(p_name), m_temperature(0), m_voltage(0)
{
	m_reader = new CSVReader("CSVFiles//Magnetorquer.csv");

	m_states.insert({ State::HEALTHY, StateData(-1, "Healthy") });
	m_states.insert({ State::TEMPERATURE_HIGH, StateData(1, "Temperature High") });
	m_states.insert({ State::TEMPERATURE_LOW, StateData(1, "Temperature Low") });
	m_states.insert({ State::TEMPERATURE_VERY_LOW, StateData(2, "Temperature Very Low") });
	m_states.insert({ State::TEMPERATURE_VERY_HIGH, StateData(2, "Temperature Very High") });
	m_states.insert({ State::VOLTAGE_HIGH, StateData(1, "Voltage High") });
	m_states.insert({ State::VOLTAGE_LOW, StateData(1, "Voltage Low") });
}

Magnetorquer::~Magnetorquer()
{
	delete m_reader;
}

void Magnetorquer::update_component_state()
{
	if ((m_temperature >= -20) && (m_temperature <= 0))
	{
		m_state = State::TEMPERATURE_LOW;
		return;
	}
	if ((m_temperature >= -30) && (m_temperature <= -21))
	{
		m_state = State::TEMPERATURE_VERY_LOW;
		return;
	}
	if ((m_temperature >= 51) && (m_temperature <= 64))
	{
		m_state = State::TEMPERATURE_HIGH;
		return;
	}
	if ((m_temperature >= 65) && (m_temperature <= 75))
	{
		m_state = State::TEMPERATURE_VERY_HIGH;
		return;
	}
	if (m_voltage - TOLERANCE < 4.8)
	{
		m_state = State::VOLTAGE_LOW;
		return;
	}
	if (m_voltage +TOLERANCE > 5.1)
	{
		m_state = State::VOLTAGE_HIGH;
		return;
	}
	
		m_state = State::HEALTHY;
	

}

void Magnetorquer::receive()
{
	vector<string> data = m_reader->readLine();

	m_temperature = stof(data.at(0));
	m_voltage = stof(data.at(1));
}
