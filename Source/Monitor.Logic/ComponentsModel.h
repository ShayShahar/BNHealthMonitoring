#pragma once

#include "Externals.h"
#include "Component.h"
#include "Components.h"
#include "../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	ComponentsModel represents the 'Components Dependency Model' (CDM).
/// 			This class exposes the CDM API to the user.
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class ComponentsModel
{
private:
	list<Component*>* m_nodes;
	list<Component*>* m_components;

	Component* lru_head;
	Component* lru_tail;

	Component* m_root;

	void create_dependencies();
	void initialzie_cdm();
	void dequeue_lru(Component* p_component);

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

