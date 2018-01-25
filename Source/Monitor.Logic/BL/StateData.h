#pragma once
#include "../Externals.h"

/* Class: StateData
   StateData class contains the component's states required data.
*/

class StateData
{
private:
	/*Variable: m_weight*/
	double m_weight;
	/*Variable: m_name*/
	string m_name;
public:
	/* Function: StateData
	Initializes a new instance of the StateData class

	Parameters:

	p_weight - State's weight
	p_name - State's name
	*/
	StateData(double p_weight, string p_name);

	/* Function: ~StateData
	Finalizes the StateData instance
	*/
	StateData();

	/* Function: name

	Returns:

	The state's name
	*/
	string name();

	/* Function: weight

	Returns:

	The state's weight
	*/
	double weight();
};
