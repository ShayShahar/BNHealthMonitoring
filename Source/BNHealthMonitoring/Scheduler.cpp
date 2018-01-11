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

void Scheduler::create_component_msg(Node* p_component, HealthMonitoringMessages::DataUpdateMsg& p_msg, HealthMonitoringMessages::OpCode p_opCode)
{
	p_msg.set_opcode(p_opCode);
	HealthMonitoringMessages::OutputMessage *resultMsgs = p_msg.mutable_result();

	HealthMonitoringMessages::pComponent* addComponent = resultMsgs->mutable_component();
	addComponent->set_name(p_component->name());
	addComponent->set_state(p_component->states()[(p_component->state())].name());
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
			Node* lru = m_cdm->handle_lru(path.back());

			HealthMonitoringMessages::DataUpdateMsg msg;
			create_component_msg(lru, msg, HealthMonitoringMessages::OpCode::LRU);
			m_communication_handler->send(msg);
		}

		HealthMonitoringMessages::DataUpdateMsg msg;
		m_cdm->get_cdm_data(msg);
		m_communication_handler->send(msg);

		HealthMonitoringMessages::DataUpdateMsg result;
		create_component_msg(path.back(), result, HealthMonitoringMessages::OpCode::Result);
		m_communication_handler->send(result);

		Sleep(5000);
	}
}

