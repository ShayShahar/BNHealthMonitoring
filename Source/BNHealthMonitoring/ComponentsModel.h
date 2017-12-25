#pragma 
#include "zmq.h"
#include "Externals.h"
#include "Node.h"

class ComponentsModel
{
private:
	HANDLE m_socket;


public:
	ComponentsModel(Node*);
	~ComponentsModel();
	Node* find_fault();

	Node* system_root;

};

