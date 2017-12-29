#pragma once
#include "../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"
#include "zmq.hpp"

class CommunicationHandler
{
private:
	static bool s_initialized;
	static CommunicationHandler* s_instance;

	zmq::context_t* m_context;
	zmq::socket_t* m_socket;

	CommunicationHandler();
public:
	~CommunicationHandler();
	static CommunicationHandler* get_instance();
	void init() const;
	void close() const;
	void send(HealthMonitoringMessages::DataUpdateMsg& p_msg) const;
};
