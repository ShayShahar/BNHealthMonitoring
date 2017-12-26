#define _CRT_SECURE_NO_WARNINGS

#include "ComponentsModel.h"
#include "Gps.h"
#include "Externals.h"

ComponentsModel::ComponentsModel(Node * root)
{
	system_root = root;

	HealthMonitoringMessages::Dummy msg;
	msg.set_name("shay");

	m_context = new zmq::context_t();
	m_socket = new zmq::socket_t(*m_context, ZMQ_REQ);
	m_socket->connect("tcp://127.0.0.1:49991");
	
	zmq::message_t sendmsg(msg.ByteSize());
	msg.SerializeToArray(sendmsg.data(), sendmsg.size());
	m_socket->send(sendmsg);

	zmq::message_t repmsg;

	bool received = m_socket->recv(&repmsg);

	if (received)
	{
		cout << received;
	}



}


ComponentsModel::~ComponentsModel()
{

}

Node * ComponentsModel::find_fault() const
{
	Node* temp = system_root;
	Node* current;
	
	while ((current = temp->get_next()) != nullptr)
	{
		temp = current;
	}

	return temp;
}
