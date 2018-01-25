#pragma once

#include "../../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"
#include "../Externals.h"
#include "Dependency.h"
#include "StateData.h"

const float TOLERANCE = 0.0001;

/* Class: Component
The component class contains the logic for each reflected component in the 'Components
Dependency Model' tree. Note that 'Component' is an abstract class. Each implemented
component must inherit 'Component' and implement the receive and update methods according to the component's unique data.
*/
class Component
{
protected:
	/*Variable: m_parent*/
	Component* m_parent;
	/*Variable: m_state*/
	int m_state;
	/*Variable: m_name*/
	string m_name;
	/*Variable: m_dependencies*/
	list<Dependency>* m_dependencies;
	/*Variable: m_weight*/
	double m_weight;
	/*Variable: m_states*/
	map<int, StateData> m_states;
	/*Variable: m_transitions*/
	Component* m_transitions[101];
	/*Variable: m_lru_next*/
	Component* m_lru_next;
	/*Variable: m_lru_prev*/
	Component* m_lru_prev;
	
public:
	/* Function: Component
	Initializes a new instance of the Component class
	*/
	Component(string p_name);

	/* Function: ~Component
	Finalizes the component instance
	*/
	virtual ~Component();

	/* Function: get_next
	Randomize the transition to the next child node.

	Returns:

    The selected child node.
	*/
	Component* get_next();

	/* Function: name
	
	Returns:

	The component's name.
	*/
	string name();

	/* Function: state

	Returns:

	The component's state.
	*/
	int state();

	/* Function: get_data
	Populate the component's message with the component's data.

	Parameters:

	p_msg - reference to the component's message.
	*/
	void get_data(HealthMonitoringMessages::pComponent* p_msg);

	/* Function: propagate_state
	Propagate the component's state upward the tree.
	*/
	void propagate_state();

	/* Function: add_dependency
	Add new component's dependency

	Parameters:

	p_dependency - dependency
	*/
	void add_dependency(Dependency p_dependency);

	/* Function: add_parent

	Set the component's parent node.

	Parameters:

	p_parent - component
	*/
	void add_parent(Component* p_parent);

	/* Function: dependencies

	Returns:

	The component's dependencies
	*/
	list<Dependency>* dependencies();

	/* Function: weight

	Returns:

	The component's weight.
	*/
	double weight();

	/* Function: notify
	Notify the parent about the updated weight.
	*/
	void notify();

	/* Function: transitions

	Returns:

	List of the available component's transitions.
	*/
	Component** transitions();

	/* Function: states

	Returns:
	
	list of the states' data.
	*/
	map<int, StateData> states();

	/* Function: lru_next

	Returns:

	The following component in the LRU queue.
	*/
	Component* lru_next();

	/* Function: lru_prev

	Returns:

	The previous component in the LRU queue.
	*/
	Component* lru_prev();


	/* Function: set_lru_next

	Set the following component in the LRU queue.

	Parameters:

	p_component - component
	*/
	void set_lru_next(Component* p_component);


	/* Function: set_lru_prev

	Set the previous component in the LRU queue.

	Parameters:

	p_component - component
	*/
	void set_lru_prev(Component* p_component);

	/* Function: update_component_state
	abstract - generate evidence from signals and set the update the link probabilities for each component
	*/
	virtual void update_component_state() = 0;

	/* Function: receive
	abstract - receive signals from the component's sensors
	*/
	virtual void receive() = 0;
};
