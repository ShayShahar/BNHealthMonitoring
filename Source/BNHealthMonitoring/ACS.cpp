#include "ACS.h"

void ACS::notify(int p_state, Node* p_sender)
{
	if (p_state == 0)
		m_state = State::HEALTHY;

	else if (p_sender->name() == "Magnetorquer")
		m_state = State::MAGNETORQUER;

	else if (p_sender->name() == "RWX")
		m_state = State::RWX;

	else if (p_sender->name() == "RWY")
		m_state = State::RWY;

	else if (p_sender->name() == "RWZ")
		m_state = State::RWZ;

	if (m_parent != nullptr)
		m_parent->notify(m_state, this);
}

ACS::ACS(string p_name, Node* p_parent) : Node(p_name, p_parent), m_voltage(0)
{
	m_reader = new CSVReader("CSVFiles//ACS.csv");
}

ACS::~ACS()
{
	delete m_reader;
}
void ACS::update_component_state()
{
	vector<string> data = m_reader->readLine();

	m_voltage = stod(data[0]);

}

string ACS::get_state_str(int p_state)
{
	switch (p_state)
	{
		case State::MAGNETORQUER:
			return "MAGNETORQUER";
		case State::RWX:
			return "RWX";		
		case State::RWY:
			return "RWY";		
		case State::RWZ:
			return "RWZ";	
	}

	return "HEALTHY";
}
