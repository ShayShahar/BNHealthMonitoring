#pragma once

#include "../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"
#include "Externals.h"
#include "Dependency.h"
#include "StateData.h"

const float TOLERANCE = 0.0001;

class Component
{
protected:
	Component* m_parent;
	int m_state;
	string m_name;
	list<Dependency>* m_dependencies;
	double m_weight;
	map<int, StateData> m_states;
	
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
	map<int, StateData> states();

	//generate evidence from signals and set the update the link probabilities for each component
	virtual void update_component_state() = 0;
	virtual void receive() = 0;
};
