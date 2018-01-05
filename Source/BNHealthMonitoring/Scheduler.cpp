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

void Scheduler::send_result(list<Node*> p_path, HealthMonitoringMessages::DataUpdateMsg& p_msg)
{
	p_msg.set_opcode(HealthMonitoringMessages::OpCode::Result);
	HealthMonitoringMessages::OutputMessage *resultMsgs = p_msg.mutable_result();

	for (list<Node*>::iterator it = p_path.begin(); it != p_path.end(); ++it)
	{
		HealthMonitoringMessages::pComponent* addComponent = resultMsgs->add_path();
		addComponent->set_name((*it)->name());
		addComponent->set_state((*it)->get_state_str((*it)->state()));
	}
}

void Scheduler::step()
{
	while (true)
	{
		m_cdm->update();
		m_cdm->propagate_states();

		list<Node*> components = m_cdm->find_fault();

		HealthMonitoringMessages::DataUpdateMsg msg;
		m_cdm->get_cdm_data(msg);
		m_communication_handler->send(msg);

		HealthMonitoringMessages::DataUpdateMsg result;
		send_result(components, result);
		m_communication_handler->send(result);


		Sleep(5000);
	}
}

