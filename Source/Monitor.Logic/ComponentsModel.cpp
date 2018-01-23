#include "ComponentsModel.h"

void ComponentsModel::create_dependencies()
{
	Satellite* satellite = new Satellite("Satellite Alpha");

	Gps* gps = new Gps("GPS");
	ACS* acs = new ACS("ACS");
	EPS* eps = new EPS("EPS");

	Magnetorquer* magnetorquer = new Magnetorquer("Magnetorquer");
	ReactionWheel* rwx = new ReactionWheel("RWX");
	ReactionWheel* rwy = new ReactionWheel("RWY");
	ReactionWheel* rwz = new ReactionWheel("RWZ");

	GpsReceiver* gps_receiver = new GpsReceiver("GPS Receiver");
	GpsAntenna* gps_antenna = new GpsAntenna("GPS Antenna");

	satellite->add_dependency(Dependency(gps));
	satellite->add_dependency(Dependency(acs));
	satellite->add_dependency(Dependency(eps));

	gps->add_dependency(Dependency(gps_receiver));
	gps->add_dependency(Dependency(gps_antenna));

	acs->add_dependency(Dependency(magnetorquer));
	acs->add_dependency(Dependency(rwx));
	acs->add_dependency(Dependency(rwy));
	acs->add_dependency(Dependency(rwz));

	m_nodes->push_back(magnetorquer);
	m_nodes->push_back(rwx);
	m_nodes->push_back(eps);
	m_nodes->push_back(rwz);
	m_nodes->push_back(rwy);
	m_nodes->push_back(gps_receiver);
	m_nodes->push_back(gps_antenna);
	m_nodes->push_back(satellite);
	m_nodes->push_back(acs);
	m_nodes->push_back(gps);

	m_root = satellite;
}

/*
   initialize node probabilities & dependencies
*/
void ComponentsModel::initialzie_cdm()
{
	for (list<Component*>::iterator it = m_nodes->begin(); it != m_nodes->end(); ++it)
	{
		if (!(*it)->dependencies()->size())
		{
			m_components->push_back((*it));

			if (lru_head == nullptr)
			{
				lru_head = (*it);
				lru_tail = (*it);

				continue;
			}

			(*it)->set_lru_prev(lru_tail);
			lru_tail->set_lru_next(*it);
			lru_tail = lru_tail->lru_next();

			continue;
		}

		int i = 0;
		int intervalLimit = 0;

		for (list<Dependency>::iterator dt = (*it)->dependencies()->begin(); dt != (*it)->dependencies()->end(); ++dt)
		{
			dt->set_probability((double)1 / (*it)->dependencies()->size());
			dt->child()->add_parent(*it);

			intervalLimit += dt->probability() * 100;

			if (&*dt == &(*it)->dependencies()->back())
				intervalLimit = 100;

			for (int j = i; j <= intervalLimit; j++, i++)
			{
				(*it)->transitions()[j] = dt->child();
			}
		}
	}
}

void ComponentsModel::dequeue_lru(Component* p_component)
{
	if (p_component != lru_tail)
	{
		if (p_component == lru_head)
		{
			lru_head = lru_head->lru_next();
			p_component->set_lru_prev(lru_tail);
			lru_tail->set_lru_next(p_component);
			lru_tail = p_component;
			lru_tail->set_lru_next(nullptr);
			lru_head->set_lru_prev(nullptr);
		}
		else
		{
			Component* next = p_component->lru_next();
			Component* prev = p_component->lru_prev();

			p_component->lru_prev()->set_lru_next(next);
			p_component->lru_next()->set_lru_prev(prev);

			p_component->set_lru_next(nullptr);
			p_component->set_lru_prev(lru_tail);
			lru_tail->set_lru_next(p_component);
			lru_tail = p_component;
		}
	}
}

Component* ComponentsModel::handle_lru(Component* p_last)
{
	dequeue_lru(p_last);

	Component* first = lru_head;

	dequeue_lru(first);

	first->update_component_state();
	first->propagate_state();

	return first;
}

ComponentsModel::ComponentsModel() : m_root(nullptr)
{
	m_nodes = new list<Component*>();
	m_components = new list<Component*>();

	lru_head = nullptr;
	lru_tail = nullptr;
}

ComponentsModel::~ComponentsModel()
{
	delete m_components;
}

void ComponentsModel::init()
{
	create_dependencies();
	initialzie_cdm();
}

list<Component*> ComponentsModel::find_fault()
{
	list<Component*> path;
	Component* temp = m_root;
	Component* current;
	path.push_back(temp);

	while ((current = temp->get_next()) != nullptr)
	{
		temp = current;
		path.push_back(temp);
	}

	return path;
}


Component* ComponentsModel::root()
{
	return m_root;
}

void ComponentsModel::receive()
{
	Component *cp = nullptr;

	try
	{
		for (list<Component*>::iterator it = m_components->begin(); it != m_components->end(); ++it)
		{
			cp = (*it);
			(*it)->receive();
		}

		m_root->receive();
	}
	catch (...)
	{
		if (cp != nullptr)
			cout << "an error occurred while try to get sensor data. component: '" << cp->name() << "'" << endl;
	}

}

list<Component*>* ComponentsModel::components()
{
	return m_components;
}

void ComponentsModel::get_cdm_data(HealthMonitoringMessages::DataUpdateMsg& p_msg)
{
	p_msg.set_opcode(HealthMonitoringMessages::OpCode::Components);
	HealthMonitoringMessages::CDMMessage *cdmMsg = p_msg.mutable_components();
	HealthMonitoringMessages::pComponent *root = cdmMsg->mutable_cdm_root();
	m_root->get_data(root);
}
