#pragma once

#include "Externals.h"
#include "Node.h"
#include "../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"
#include "Components.h"

class ComponentsModel
{
private:
	list<Node*>* m_components;
	Node* m_root;

public:
	ComponentsModel();
	~ComponentsModel();
	void init();
	list<Node*> find_fault();
	void get_cdm_data(HealthMonitoringMessages::DataUpdateMsg& p_msg);
	void update();
	Node* root();
};

