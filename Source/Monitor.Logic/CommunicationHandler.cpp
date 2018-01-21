#include "CommunicationHandler.h"
#include "IniReader.h"

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
	INIReader reader("config.ini");
	string ip = "127.0.0.1";
	int port = 49993;

	if (reader.ParseError() < 0) 
	{
		std::cout << "Can't load 'config.ini', using default endpoint: 127.0.0.1:49993" << endl;;
	}
	else
	{
		ip = reader.Get("TCP", "HostIp", "UNKNOWN");
		port = reader.GetInteger("TCP", "Port", -1);

		if (ip == "UNKNOWN")
		{
			std::cout << "couldn't load IP address from config.ini. using default: '127.0.0.1'" << endl;
			ip = "127.0.0.1";
		}
		else
		{
			std::cout << "Config loaded from 'config.ini': IP=" << ip << endl;
		}

		if (port == -1)
		{
			std::cout << "couldn't load port from config.ini. using default: '49993'" << endl;
			port = 49993;
		}
		else
		{
			std::cout << "Config loaded from 'config.ini': Port=" << port << endl;
		}

	}

	std::cout << "Establishing connection [" << ip << ":" << port << "]" << endl;

	std::stringstream connStream;
	connStream << "tcp://" << ip << ":" << port;
	
	try
	{
		m_socket->bind(connStream.str());
		std::cout << "Connected." << endl;
	}
	catch(...)
	{
		std::cout << "ERROR: Couldn't create socket." << endl;
	}
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
