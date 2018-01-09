#include "GpsReceiver.h"

GpsReceiver::GpsReceiver(string p_name) : Node(p_name), m_temperature(0), m_shock(0), m_voltage(0)
{
	m_reader = new CSVReader("CSVFiles//GpsReceiver.csv");

	m_states.insert({ State::HEALTHY, StateData(-0.5, "Healthy") });
	m_states.insert({ State::TEMPERATURE_HIGH, StateData(1, "Temperature High") });
	m_states.insert({ State::TEMPERATURE_LOW, StateData(1, "Temperature Low") });
	m_states.insert({ State::TEMPERATURE_VERY_LOW, StateData(2, "Temperature Very Low") });
	m_states.insert({ State::TEMPERATURE_VERY_HIGH, StateData(2, "Temperature Very High") });
	m_states.insert({ State::SHOCK_HIGH, StateData(1.3, "Shock") });
	m_states.insert({ State::VOLTAGE_HIGH, StateData(1, "Voltage High") });
	m_states.insert({ State::VOLTAGE_LOW, StateData(1, "Voltage Low") });
}

GpsReceiver::~GpsReceiver()
{
	delete m_reader;
}

void GpsReceiver::update_component_state()
{
	if (-30 < m_temperature && m_temperature < 0)
	{
		m_state = State::TEMPERATURE_LOW;
		return;
	}

	if (-40 < m_temperature && m_temperature < -31)
	{
		m_state = State::TEMPERATURE_VERY_LOW;
		return;
	}

	if (71 < m_temperature && m_temperature < 80)
	{
		m_state = State::TEMPERATURE_HIGH;
		return;
	}

	if (81 < m_temperature && m_temperature < 85)
	{
		m_state = State::TEMPERATURE_VERY_HIGH;
		return;
	}

	if (31 < m_shock && m_temperature < 40)
	{
		m_state = State::SHOCK_HIGH;
		return;
	}

	if (m_voltage > 3.3)
	{
		m_state = State::VOLTAGE_HIGH;
		return;
	}

	if (m_voltage < 3.3)
	{
		m_state = State::VOLTAGE_LOW;
		return;
	}

	m_state = State::HEALTHY;
}

void GpsReceiver::receive()
{
	vector<string> data = m_reader->readLine();

	m_temperature = stod(data[0]);
	m_shock = stod(data[1]);
	m_voltage = stod(data[2]);
}
