#include "Magnetorquer.h"

Magnetorquer::Magnetorquer(string p_name) : Node(p_name), m_temperature(0), m_voltage(0)
{
	m_reader = new CSVReader("CSVFiles//Magnetorquer.csv");
}

Magnetorquer::~Magnetorquer()
{
	delete m_reader;
}

void Magnetorquer::update_component_state()
{
	if ((m_temperature > -20) && (m_temperature < 0))
	{
		m_state = State::TEMPERATURE_LOW;
		return;
	}
	if ((m_temperature > -30) && (m_temperature < -20))
	{
		m_state = State::TEMPERATURE_VERY_LOW;
		return;
	}
	if ((m_temperature > 51) && (m_temperature < 64))
	{
		m_state = State::TEMPERATURE_HIGH;
		return;
	}
	if ((m_temperature > 65) && (m_temperature < 75))
	{
		m_state = State::TEMPERATURE_VERY_HIGH;
		return;
	}
	if (m_voltage < 5)
	{
		m_state = State::VOLTAGE_LOW;
		return;
	}
	if (m_voltage > 5)
	{
		m_state = State::VOLTAGE_HIGH;
		return;
	}
	
		m_state = State::HEALTHY;
	

}

void Magnetorquer::receive()
{
	vector<string> data = m_reader->readLine();

	m_temperature = stod(data[0]);
	m_voltage = stod(data[1]);
}
