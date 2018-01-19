#pragma once

#include "Externals.h"
#include "Component.h"
#include "../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"
#include "Components.h"

class ComponentsModel
{
private:
	list<Component*>* m_nodes;
	list<Component*>* m_components;
	deque<Component*>* m_lru;

	Component* m_root;

	void create_dependencies();
	void initialzie_cdm();

public:
	ComponentsModel();
	~ComponentsModel();
	void init();
	list<Component*> find_fault();
	void get_cdm_data(HealthMonitoringMessages::DataUpdateMsg& p_msg);
	Component* root();
	void receive();
	list<Component*>* components();
	Component* handle_lru(Component* p_last);
};

