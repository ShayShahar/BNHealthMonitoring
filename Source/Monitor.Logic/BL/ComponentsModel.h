#pragma once

#include "../Externals.h"
#include "Component.h"
#include "../Components.h"
#include "../../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"

/* Class: ComponentsModel
   ComponentsModel represents the 'Components Dependency Model' (CDM).
   This class exposes the CDM API to the user.
*/

class ComponentsModel
{
private:
	/*Variable: m_nodes*/
	list<Component*>* m_nodes;
	
	list<Component*>* m_components;
	/*Variable: m_components*/

	/*Variable: lru_head*/
	Component* lru_head;

	/*Variable: lru_tail*/
	Component* lru_tail;
	
	/*Variable: m_root*/
	Component* m_root;

	/* Function: create_dependencies
	Link between the dependencies to the nodes
	*/
	void create_dependencies();

	/* Function: initialzie_cdm
	Create the components' dependencies
	*/
	void initialzie_cdm();

	/* Function: dequeue_lru
	Remove a node from the LRU queue and enqueue it back in order to maintain the cyclic structure.
	*/
	void dequeue_lru(Component* p_component);

public:
	/* Function: ComponentsModel
	Initializes a new instance of the ComponentsModel class
	*/
	ComponentsModel();

	/* Function: ~ComponentsModel
	Finalizes an instance of the ComponentsModel*/
	~ComponentsModel();

	/* Function: init
	initialize the instance of the components model*/
	void init();

	/* Function: find_fault
	Randomize path from the root node to any child.

	Returns:

	The selected child node.
	*/
	list<Component*> find_fault();

	/* Function: get_cdm_data
	create a message which contains the CDM data.

	Parameters:
	
	p_msg - reference to the message structure

	*/
	void get_cdm_data(HealthMonitoringMessages::DataUpdateMsg& p_msg);

	/* Function: receive
	call receive function for all the implemented components*/
	void receive();

	/* Function: components

	Returns:
	list of the reflected components*/
	list<Component*>* components();

	/* Function: handle_lru

	Returns:
	the least recently updated component
	
	Parameters:
	
	p_last - the selected component from the find_fault result
	*/
	Component* handle_lru(Component* p_last);

	/* Function: root

	Returns:

	Components tree root node*/
	Component* root();
};

