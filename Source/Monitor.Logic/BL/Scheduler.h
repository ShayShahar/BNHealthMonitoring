#pragma once
#include <thread>
#include "CommunicationHandler.h"
#include "ComponentsModel.h"

/*
Class: Scheduler
The Scheduler class demonstrate the satellite's operation system cycle in order to run the module.
*/
class Scheduler
{
private:
	/*Variable: m_thread*/
	thread* m_thread;
	/*Variable: m_communication_handler*/
	CommunicationHandler* m_communication_handler;
	/*Variable: m_cdm*/
	ComponentsModel* m_cdm;

private:
	/* Function: step
	   includes the algorithm's 2 phases cycle.
	*/
	void step();

	/* Function: create_component_msg
	   send the algorithm's result to subscribers.

	   Parameters:
	   p_component  - the result
	   p_msg - reference to the DataUpdateMsg.builder which will be send to the subscribers.
	   p_opCode - message OpCode
	*/
	void Scheduler::create_component_msg(Component* p_component, HealthMonitoringMessages::DataUpdateMsg& p_msg,
		HealthMonitoringMessages::OpCode p_opCode);

public:

	/* Function: Scheduler
	   Constructor
	*/
	Scheduler();

	/* Function: ~Scheduler
	Finalizes the Scheduler instance
	*/
	~Scheduler();

	/* Function: init
	Initialize all module's components.
	*/
	void init();

	/* Function: join
		Keep the main thread alive by calling this function
	*/
	void join();
};
