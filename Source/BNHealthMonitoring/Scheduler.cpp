#include "Scheduler.h"

Scheduler::Scheduler()
{
	m_communication_handler = CommunicationHandler::get_instance();
	m_cdm = new ComponentsModel();
}

Scheduler::~Scheduler()
{
	delete m_thread;
	m_communication_handler->close();
	delete m_communication_handler;
	delete m_cdm;
}

void Scheduler::init()
{
	m_cdm->init();
	m_communication_handler->init();
	m_thread = new thread(&Scheduler::step, this);
}

void Scheduler::join() const
{
	m_thread->join();
}

void Scheduler::step() const
{
	while (true)
	{
		m_cdm->update();
		list<Node*> component = m_cdm->find_fault();

		HealthMonitoringMessages::DataUpdateMsg msg;
		m_cdm->get_cdm_data(msg);
		m_communication_handler->send(msg);

		Sleep(20000);
	}
}
