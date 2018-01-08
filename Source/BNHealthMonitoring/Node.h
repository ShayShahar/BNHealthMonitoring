#pragma once

#include "../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"
#include "Externals.h"
#include "Dependency.h"
#include "StateData.h"

class Node
{
protected:
	Node* m_parent;
	int m_state;
	string m_name;
	list<Dependency>* m_dependencies;
	unsigned int m_count;
	double m_weight;
	map<int, StateData> m_states;

public:
	Node(string p_name);
	virtual ~Node();
	Node* get_next();
	string name();
	int state();
	void get_data(HealthMonitoringMessages::pComponent* p_msg);
	void propagate_state();
	void add_dependency(Dependency p_dependency);
	void add_parent(Node* p_parent);
	list<Dependency>* dependencies();
	double weight();

	void notify();
	virtual string get_state_str(int p_state) = 0;

	//generate evidence from signals and set the update the link probabilities for each component
	virtual void update_component_state() = 0;
};
