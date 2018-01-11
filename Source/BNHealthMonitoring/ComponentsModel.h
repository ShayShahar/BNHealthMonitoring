#pragma once

#include "Externals.h"
#include "Node.h"
#include "../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"
#include "Components.h"

class ComponentsModel
{
private:
	list<Node*>* m_nodes;
	list<Node*>* m_components;
	deque<Node*>* m_lru;

	Node* m_root;

	void create_dependencies();
	void initialzie_cdm();

public:
	ComponentsModel();
	~ComponentsModel();
	void init();
	list<Node*> find_fault();
	void get_cdm_data(HealthMonitoringMessages::DataUpdateMsg& p_msg);
	Node* root();
	void receive();
	list<Node*>* components();
	Node* handle_lru(Node* p_last);
};

