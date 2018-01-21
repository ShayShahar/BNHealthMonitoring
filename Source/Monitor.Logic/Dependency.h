#pragma once

class Component;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Dependency class contains the link data between 2 components in the 'Components Dependency Model'. 
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

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
