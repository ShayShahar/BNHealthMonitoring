#pragma once
#include "../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"
#include "zmq.hpp"
#include "ComponentsModel.h"

class CommunicationHandler
{
private:
	zmq::context_t* m_context;
	zmq::socket_t* m_socket;
	//zmq::socket_t* m_replySocket;
	ComponentsModel& m_cdm;
	std::thread* m_thread;
	
public:
	CommunicationHandler(ComponentsModel& p_cdm);
	~CommunicationHandler();
	void message_polling();
	void step();
	void init();
	void join();
};
