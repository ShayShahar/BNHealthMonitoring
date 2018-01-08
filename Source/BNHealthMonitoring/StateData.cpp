#include "StateData.h"

StateData::StateData(double p_weight, string p_name)
{
	m_name = p_name;
	m_weight = p_weight;
}

string StateData::name()
{
	return m_name;
}

double StateData::weight()
{
	return m_weight;
}
