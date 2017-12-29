#pragma once

#include "Link.h"
#include "../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"
#include "Externals.h"
#include "Utils.h"

class Node
{
protected:
	int m_state;
	string m_name;
	std::map<int, list<Link>*> m_probabilities;

public:
	Node(string p_name);
	virtual ~Node();
	Node* get_next();
	void add_link(unsigned int p_state, Link p_link);
	string name();
	map<int, list<Link>*> links();
	int state();
	void get_data(HealthMonitoringMessages::pComponent* p_msg);

	//generate evidence from signals and set the update the link probabilities for each component
	virtual void update_component_state() = 0;
};
