#include "Gps.h"

Gps::Gps(string p_name) : Node(p_name)
{

}

Gps::~Gps()
{
}

void Gps::update_component_state()
{
}

string Gps::get_state_str(int p_state)
{
	return "HEALTHY";
}


void Gps::notify(int p_state, Node* p_sender)
{
	//if (p_state == 0)
	//	m_state = State::HEALTHY;

	//else if (p_sender->name() == "GPS Receiver")
	//	m_state = State::RECEIVER;

	//else if (p_sender->name() == "GPS Antenna")
	//	m_state = State::ANTENNA;

	//if (m_parent != nullptr)
	//	m_parent->notify(m_state, this);
}

