#pragma once

class Component;

class Dependency
{
private:
	Component* m_node;
	double m_probability;
public:
	Dependency(Component* p_child);
	~Dependency();
	Component* child();
	double probability();
	void set_probability(double p_probability);
};
