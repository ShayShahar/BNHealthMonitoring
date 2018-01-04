#include "ReactionWeel.h"

void ReactionWeel::notify(int p_state, Node* p_sender)
{
}

ReactionWeel::ReactionWeel(string p_name, Node* p_parent) : Node(p_name, p_parent)
{ 
	m_reader = new CSVReader("CSVFiles//RWX.csv");
}

ReactionWeel::~ReactionWeel()
{
	delete m_reader;
}

void ReactionWeel::update_component_state()
{
	vector<string> data = m_reader->readLine();

	m_temperature = stod(data[0]);
	m_voltage = stod(data[1]);
}

string ReactionWeel::get_state_str(int p_state)
{
	switch (p_state)
	{
	case State::VOLTAGE:
		return "VOLTAGE";
	case State::TEMPERATURE:
		return "TEMPERATURE";
	}

	return "HEALTHY";
}
