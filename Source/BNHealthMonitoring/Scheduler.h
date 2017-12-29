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
	void step() const;

public:
	Scheduler();
	~Scheduler();
	void init();
	void join() const;
};
