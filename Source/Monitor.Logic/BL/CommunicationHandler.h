#pragma once
#include "../../../Source/Interfaces/Messages/HealthMonitoringMessages.pb.h"
#include "zmq.hpp"
#include "../Externals.h"

/*Class: CommunicationHandler
		 A communication handler class which manages the application's sockets.
		 In order to get an instance of CommunicationHandler you should call the "get_instance" method.
		 Note that this class implements the singleton pattern, which restricts the instantiation of the class to one object.
*/
class CommunicationHandler
{
private:
	/*Variable: s_initialized*/
	static bool s_initialized;

	/*Variable: s_instance*/
	static CommunicationHandler* s_instance;

	/*Variable: m_context*/
	zmq::context_t* m_context;

	/*Variable: m_socket*/
	zmq::socket_t* m_socket;

	/* Function: CommunicationHandler
	Prevents a default instance of the CommunicationHandler class from being created.*/
	CommunicationHandler();
public:

	/* Function: ~CommunicationHandler
	Finalizes an instance of the CommunicationHandler*/
	~CommunicationHandler();

	/* Function: get_instance
	returns the instance of CommunicationHandler*/
	static CommunicationHandler* get_instance();

	/* Function: init
	Initializes the communication handler.
	*/
	void init() const;

	/* Function: close
	Close the sockets
	*/
	void close() const;

	/* Function: send
	Publish data message to subscribers.

	Parameters:
	p_msg - The message
	*/
	void send(HealthMonitoringMessages::DataUpdateMsg& p_msg) const;
};

