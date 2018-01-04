#include "Satellite.h"

void Sattelite::notify(int p_state, Node* p_sender)
{
	if (p_state == 0)
		m_state = State::HEALTHY;

	else if (p_sender->name() == "ACS")
		m_state = State::ACS;

	else if (p_sender->name() == "EPS")
		m_state = State::EPS;

	else if (p_sender->name() == "GPS")
		m_state = State::GPS;

	if (m_parent != nullptr)
		m_parent->notify(m_state, this);
}

Sattelite::Sattelite(string p_name, Node* p_parent) : Node(p_name, p_parent)
{
}

Sattelite::~Sattelite()
{
}

void Sattelite::update_component_state()
{
}

string Sattelite::get_state_str(int p_state)
{
	switch (p_state)
	{
		case State::ACS:
			return "ACS";
		case State::EPS:
			return "EPS";	
		case State::GPS:
			return "GPS";
	}

	return "HEALTHY";
}
