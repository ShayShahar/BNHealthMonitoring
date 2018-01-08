#include "GpsReceiver.h"

GpsReceiver::GpsReceiver(string p_name) : Node(p_name), m_temperature(0), m_shock(0), m_voltage(0)
{
	m_reader = new CSVReader("CSVFiles//GpsReceiver.csv");

	//example 
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
	vector<string> data = m_reader->readLine();

	m_temperature = stod(data[0]);
	m_shock = stod(data[1]);
	m_voltage = stod(data[2]);

	if ((1 < m_temperature < 60) && (0 < m_shock < 30) && (m_voltage == 3.3))
	{
		m_state = State::HEALTHY;
	}
	else if (-30 < m_temperature < 0)
	{
		m_state = State::TEMPERATURE_LOW;
	}
	else if (-40 < m_temperature < -31)
	{
		m_state = State::TEMPERATURE_VERY_LOW;
	}
	else if (71 < m_temperature < 80)
	{
		m_state = State::TEMPERATURE_HIGH;
	}
	else if (81 < m_temperature < 85)
	{
		m_state = State::TEMPERATURE_VERY_HIGH;
	}
	else if (31 < m_shock < 40)
	{
		m_state = State::SHOCK_HIGH;
	}
	else if (m_voltage > 3.3)
	{
		m_state = State::VOLTAGE_HIGH;
	}
	else if (m_voltage < 3.3)
	{
		m_state = State::VOLTAGE_LOW;
	}
		
	

}

string GpsReceiver::get_state_str(int p_state)
{
	return string();
}
