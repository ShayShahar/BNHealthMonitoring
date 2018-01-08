#include "StateData.h"

StateData::StateData(double weight, string name)
{
	m_name = name;
	m_weight = weight;
}
StateData::StateData() {};

string StateData::name()
{
	return m_name;
}

double StateData::weight()
{
	return m_weight;
}
