#pragma once
#include <thread>
#include "CommunicationHandler.h"
#include "ComponentsModel.h"


class Scheduler
{
private:
	std::thread* m_thread;
	CommunicationHandler* m_communication_handler;
	ComponentsModel* m_cdm;

private:
	void step();
	void Scheduler::create_component_msg(Component* p_component, HealthMonitoringMessages::DataUpdateMsg& p_msg, 
		HealthMonitoringMessages::OpCode p_opCode);

public:
	Scheduler();
	~Scheduler();
	void init();
	void join();
};
