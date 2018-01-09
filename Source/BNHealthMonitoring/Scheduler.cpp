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

void Scheduler::join() 
{
	m_thread->join();

}

void Scheduler::populate_list_msg(list<Node*> p_path, HealthMonitoringMessages::DataUpdateMsg& p_msg)
{
	HealthMonitoringMessages::OutputMessage *resultMsgs = p_msg.mutable_result();

	for (list<Node*>::iterator it = p_path.begin(); it != p_path.end(); ++it)
	{
		HealthMonitoringMessages::pComponent* addComponent = resultMsgs->add_path();
		addComponent->set_name((*it)->name());
		addComponent->set_state((*it)->states()[((*it)->state())].name());
	}
}

void Scheduler::step()
{
	while (true)
	{
		m_cdm->receive();

		list<Node*> path = m_cdm->find_fault();

		if (path.size() > 0)
		{
			path.back()->update_component_state();
			path.back()->propagate_state();
		}
			
		HealthMonitoringMessages::DataUpdateMsg msg;
		m_cdm->get_cdm_data(msg);
		m_communication_handler->send(msg);

		HealthMonitoringMessages::DataUpdateMsg result;
		result.set_opcode(HealthMonitoringMessages::OpCode::Result);
		populate_list_msg(path, result);
		m_communication_handler->send(result);

		Sleep(5000);
	}
}

