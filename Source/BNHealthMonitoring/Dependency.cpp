#include "Dependency.h"

Dependency::Dependency(Component * p_child): m_probability(0)
{
	m_node = p_child;
}

Dependency::~Dependency()
{
}

Component * Dependency::child()
{
	return m_node;
}

double Dependency::probability()
{
	return m_probability;
}

void Dependency::set_probability(double p_probability)
{
	m_probability = p_probability;
}
