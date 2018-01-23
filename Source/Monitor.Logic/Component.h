#pragma once

#include "../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"
#include "Externals.h"
#include "Dependency.h"
#include "StateData.h"

const float TOLERANCE = 0.0001;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	The component class contains the logic for each reflected component in the 'Components 
///				Dependency Model' tree.
///				Note that 'Component' is an abstract class. Each implemented component must inherit 'Component'
///				and implement the receive and update methods according to the component's unique data.
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class Component
{
protected:
	Component* m_parent;
	int m_state;
	string m_name;
	list<Dependency>* m_dependencies;
	double m_weight;
	map<int, StateData> m_states;
	Component* m_transitions[101];
	
public:
	Component(string p_name);
	virtual ~Component();
	Component* get_next();
	string name();
	int state();
	void get_data(HealthMonitoringMessages::pComponent* p_msg);
	void propagate_state();
	void add_dependency(Dependency p_dependency);
	void add_parent(Component* p_parent);
	list<Dependency>* dependencies();
	double weight();
	void notify();
	Component** transitions();
	map<int, StateData> states();

	//generate evidence from signals and set the update the link probabilities for each component
	virtual void update_component_state() = 0;
	virtual void receive() = 0;
};
