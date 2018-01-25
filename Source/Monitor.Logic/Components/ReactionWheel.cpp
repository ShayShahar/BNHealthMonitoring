// ***********************************************************************
// Assembly         : 
// Author           : shays
// Created          : 01-04-2018
//
// Last Modified By : shays
// Last Modified On : 01-23-2018
// ***********************************************************************
// <copyright file="ReactionWeel.cpp" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "ReactionWheel.h"

/// <summary>
/// Initializes a new instance of the <see cref="ReactionWheel"/> class.
/// </summary>
/// <param name="p_name">Name of the p.</param>
ReactionWheel::ReactionWheel(string p_name) : Component(p_name)
{ 
	if(p_name == "RWX")
		m_reader = new CSVReader("CSVFiles//RWX.csv");
	else if (p_name == "RWY")
		m_reader = new CSVReader("CSVFiles//RWY.csv");
	else
		m_reader = new CSVReader("CSVFiles//RWZ.csv");

	m_states.insert({ State::HEALTHY, StateData(-1, "Healthy") });
	m_states.insert({ State::TEMPERATURE_HIGH, StateData(1, "Temperature High") });
	m_states.insert({ State::TEMPERATURE_LOW, StateData(1, "Temperature Low") });
	m_states.insert({ State::TEMPERATURE_VERY_LOW, StateData(2, "Temperature Very Low") });
	m_states.insert({ State::TEMPERATURE_VERY_HIGH, StateData(2, "Temperature Very High") });
	m_states.insert({ State::VOLTAGE_HIGH, StateData(1, "Voltage High") });
	m_states.insert({ State::VOLTAGE_LOW, StateData(1, "Voltage Low") });
}

/// <summary>
/// Finalizes an instance of the <see cref="ReactionWheel"/> class.
/// </summary>
ReactionWheel::~ReactionWheel()
{
	delete m_reader;
}

/// <summary>
/// Updates the state of the component.
/// </summary>
void ReactionWheel::update_component_state()
{
	if ((m_temperature >= -19) && (m_temperature <= 0))
	{
		m_state = State::TEMPERATURE_LOW;
		return;
	}
	if ((m_temperature >= -40) && (m_temperature <= -20))
	{
		m_state = State::TEMPERATURE_VERY_LOW;
		return;
	}
	if ((m_temperature >= 50) && (m_temperature <= 59))
	{
		m_state = State::TEMPERATURE_HIGH;
		return;
	}
	if ((m_temperature >= 60) && (m_temperature <= 70))
	{
		m_state = State::TEMPERATURE_VERY_HIGH;
		return;
	}
	if ((m_voltage >= 3.4) && (m_voltage <= 3.9))
	{
		m_state = State::VOLTAGE_LOW;
		return;
	}
	if ((m_voltage >= 6.1) && (m_voltage <= 8))
	{
		m_state = State::VOLTAGE_HIGH;
		return;
	}
	
		m_state = State::HEALTHY;
	

}

/// <summary>
/// Receives this instance.
/// </summary>
void ReactionWheel::receive()
{
	vector<string> data = m_reader->readLine();

	m_temperature = stof(data.at(0));
	m_voltage = stof(data.at(1));
}
