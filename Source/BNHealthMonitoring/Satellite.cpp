#include "Satellite.h"

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
