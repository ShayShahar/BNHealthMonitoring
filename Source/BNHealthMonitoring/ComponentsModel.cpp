#include "ComponentsModel.h"
#include "Gps.h"


ComponentsModel::ComponentsModel(Node * root)
{
	system_root = root;
	HANDLE context = zmq_ctx_new();
	m_socket = zmq_socket(context, ZMQ_REQ);
	zmq_connect(m_socket, "tcp://localhost:49991");

	zmq_msg_t msg;
	string data = "hi";
	//zmq_msg_init_data(&msg, data, 2,NULL, NULL);
	//zmq_msg_send()
	

}


ComponentsModel::~ComponentsModel()
{
}

Node * ComponentsModel::find_fault()
{
	Node* temp = system_root;
	Node* current;
	
	while ((current = temp->get_next()) != nullptr)
	{
		temp = current;
	}

	return temp;
}
