#include "CommunicationHandler.h"

bool CommunicationHandler::s_initialized = false;
CommunicationHandler* CommunicationHandler::s_instance = nullptr;

CommunicationHandler::CommunicationHandler()
{
	m_context = new zmq::context_t();
	m_socket = new zmq::socket_t(*m_context, ZMQ_PUB);
}

CommunicationHandler::~CommunicationHandler()
{
	s_initialized = false;
}

CommunicationHandler* CommunicationHandler::get_instance()
{
	if (!s_initialized)
	{
		s_instance = new CommunicationHandler();
		s_initialized = true;
	}

	return s_instance;
}

void CommunicationHandler::init() const
{
	m_socket->bind("tcp://127.0.0.1:49993");
}

void CommunicationHandler::close() const
{
	m_socket->unbind("tcp://127.0.0.1:49993");
	m_socket->close();
}

void CommunicationHandler::send(HealthMonitoringMessages::DataUpdateMsg& p_msg) const
{
	zmq::message_t sendmsg(p_msg.ByteSize());
	p_msg.SerializeToArray(sendmsg.data(), sendmsg.size());
	m_socket->send(sendmsg);
}
