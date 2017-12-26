#pragma 
#include "zmq.hpp"
#include "Externals.h"
#include "Node.h"
#include "../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"

class ComponentsModel
{
private:
	zmq::context_t* m_context;
	zmq::socket_t* m_socket;

public:
	ComponentsModel(Node*);
	~ComponentsModel();
	Node* find_fault() const;

	Node* system_root;
};

