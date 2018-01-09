#include "EPS.h"


EPS::EPS(string p_name) : Node(p_name)
{
	m_reader = new CSVReader("CSVFiles//EPS.csv");
}

EPS::~EPS()
{
	delete m_reader;
}

void EPS::update_component_state()
{
	if ((m_temperature > -10) && (m_temperature < 0))
	{
		m_state = State::TEMPERATURE_LOW;
		return;
	}
	if ((m_temperature > -20) && (m_temperature < -11))
	{
		m_state = State::TEMPERATURE_VERY_LOW;
		return;
	}
	if ((m_temperature > 40) && (m_temperature < 50))
	{
		m_state = State::TEMPERATURE_HIGH;
		return;
	}
	if ((m_temperature > 51) && (m_temperature < 60))
	{
		m_state = State::TEMPERATURE_VERY_HIGH;
		return;
	}
	if (m_voltage < 3)
	{
		m_state = State::VOLTAGE_LOW;
		return;
	}
	if (m_voltage > 4.2)
	{
		m_state = State::VOLTAGE_HIGH;
		return;
	}
	
		m_state = State::HEALTHY;

}

void EPS::receive()
{
	vector<string> data = m_reader->readLine();

	m_temperature = stod(data[0]);
	m_voltage = stod(data[1]);
}

