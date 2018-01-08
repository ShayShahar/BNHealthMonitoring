#include "Dependency.h"

Dependency::Dependency(Node * p_child): m_probability(0)
{
	m_node = p_child;
}

Dependency::~Dependency()
{
}

Node * Dependency::child()
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
