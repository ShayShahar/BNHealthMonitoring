#pragma once
#include "zmq.hpp"
#include "Externals.h"
#include "Node.h"
#include "../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"

class ComponentsModel
{
public:
	ComponentsModel(Node*);
	~ComponentsModel();
	Node* find_fault() const;
	void publish(HealthMonitoringMessages::DataReplyMsg& p_msg);

	Node* system_root;
};

