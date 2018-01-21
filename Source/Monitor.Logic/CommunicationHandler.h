#pragma once
#include "../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"
#include "zmq.hpp"
#include "Externals.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A communication handler class which manages the application's sockets.
/// 		    In order to get an instance of CommunicationHandler you should call the "get_instance" method.
///			    Note that this class implemented the singleton pattern, which restricts the 
///             instantiation  of the class to one object. 
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

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
