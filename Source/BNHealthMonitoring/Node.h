#pragma once

#include "Link.h"
#include "../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"
#include "Externals.h"
#include "Utils.h"

class Node
{
protected:
	Node* m_parent;
	int m_state;
	string m_name;
	std::map<int, list<Link>*> m_probabilities;

public:
	Node(string p_name, Node* p_parent);
	virtual ~Node();
	Node* get_next();
	void add_link(unsigned int p_state, Link p_link);
	string name();
	map<int, list<Link>*> links();
	int state();
	void get_data(HealthMonitoringMessages::pComponent* p_msg);
	void propagate_state();

	virtual string get_state_str(int p_state) = 0;
	//generate evidence from signals and set the update the link probabilities for each component
	virtual void update_component_state() = 0;
	virtual void notify(int p_state, Node* p_sender) = 0;
};
