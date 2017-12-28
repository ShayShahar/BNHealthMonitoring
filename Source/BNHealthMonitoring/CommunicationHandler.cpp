#include "CommunicationHandler.h"

CommunicationHandler::CommunicationHandler(ComponentsModel& p_cdm) : m_cdm(p_cdm)
{
	m_context = new zmq::context_t();
	m_socket = new zmq::socket_t(*m_context, ZMQ_PUB);
	//m_socket->setsockopt(ZMQ_SUBSCRIBE, "", 1);
	//m_replySocket = new zmq::socket_t(*m_context, ZMQ_REP);
}

CommunicationHandler::~CommunicationHandler()
{
}

void CommunicationHandler::message_polling()
{
	while (true)
	{



		//zmq::message_t repmsg;
		//bool received = m_replySocket->recv(&repmsg);

		//HealthMonitoringMessages::DataRequestMsg msg;
		//msg.ParseFromArray(repmsg.data(), repmsg.size());

		//if (received)
		//{
		//	HealthMonitoringMessages::DataReplyMsg result;
		//	result.set_opcode(HealthMonitoringMessages::Components);

		//	zmq::message_t sendmsg(result.ByteSize());
		//	result.SerializeToArray(sendmsg.data(), sendmsg.size());
		//	m_replySocket->send(sendmsg);
		//}

	}
}

void CommunicationHandler::step()
{
	while (true)
	{
		HealthMonitoringMessages::DataReplyMsg msg;
		msg.set_opcode(HealthMonitoringMessages::OpCode::Components);
		HealthMonitoringMessages::CDMMessage *cdmMsg = msg.mutable_components();
		HealthMonitoringMessages::pComponent *root = cdmMsg->mutable_cdm_root();
		m_cdm.system_root->get_data(root);

		zmq::message_t sendmsg(msg.ByteSize());
		msg.SerializeToArray(sendmsg.data(), sendmsg.size());
		m_socket->send(sendmsg);

		Sleep(700);
	}
}

void CommunicationHandler::init()
{
	//	m_replySocket->bind("tcp://127.0.0.1:49992");
	m_socket->bind("tcp://127.0.0.1:49993");

	m_thread = new thread(&CommunicationHandler::step, this);
}

void CommunicationHandler::join()
{
	m_thread->joinable();
}

