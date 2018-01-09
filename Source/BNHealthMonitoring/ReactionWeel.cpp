#include "ReactionWeel.h"

ReactionWeel::ReactionWeel(string p_name) : Node(p_name)
{ 
	m_reader = new CSVReader("CSVFiles//RWX.csv");
}

ReactionWeel::~ReactionWeel()
{
	delete m_reader;
}

void ReactionWeel::update_component_state()
{

}

void ReactionWeel::receive()
{
	vector<string> data = m_reader->readLine();

	m_temperature = stod(data[0]);
	m_voltage = stod(data[1]);
}
