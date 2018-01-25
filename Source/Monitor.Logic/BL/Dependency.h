#pragma once

class Component;

/* Class: Dependency
   Dependency class contains the link data between 2 components in the 'Components Dependency Model'.
*/
class Dependency
{
private:
	/*Variable: m_node*/
	Component* m_node;
	/*Variable: m_probability*/
	double m_probability;
public:
	/* Function: Dependency
	Initializes a new instance of the Dependency class

	Parameters:

	p_child - child node
	*/
	Dependency(Component* p_child);

	/* Function: ~Dependency
	Finalizes the Dependency instance
	*/
	~Dependency();

	/* Function: child
	
	Returns:

	The child node
	*/
	Component* child();


	/* Function: probability

	Returns:

	The transition's probability
	*/
	double probability();

	/* Function: Dependency
	Update the transition's probability

	Parameters:

	p_probability - probability
	*/
	void set_probability(double p_probability);
};
