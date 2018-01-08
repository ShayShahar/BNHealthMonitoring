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

