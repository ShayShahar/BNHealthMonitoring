#include "ComponentsModel.h"

void ComponentsModel::create_dependencies()
{
	Sattelite* satellite = new Sattelite("Satellite Alpha");

	Gps* gps = new Gps("GPS");
	ACS* acs = new ACS("ACS");
	EPS* eps = new EPS("EPS");

	Magnetorquer* magnetorquer = new Magnetorquer("Magnetorquer");
	ReactionWeel* rwx = new ReactionWeel("RWX");
	ReactionWeel* rwy = new ReactionWeel("RWY");
	ReactionWeel* rwz = new ReactionWeel("RWZ");

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
	m_nodes->push_back(rwz);
	m_nodes->push_back(rwy);
	m_nodes->push_back(gps_receiver);
	m_nodes->push_back(gps_antenna);
	m_nodes->push_back(eps);
	m_nodes->push_back(satellite);
	m_nodes->push_back(acs);
	m_nodes->push_back(gps);

	m_root = satellite;
}

/*
   initialize node probabilities & dephendencies
*/
void ComponentsModel::initialzie_cdm()
{
	for (list<Node*>::iterator it = m_nodes->begin(); it != m_nodes->end(); ++it)
	{
		if (!(*it)->dependencies()->size())
		{
			m_components->push_back((*it));
			m_lru->push_front((*it));
			continue;
		}

		for (list<Dependency>::iterator dt = (*it)->dependencies()->begin(); dt != (*it)->dependencies()->end(); ++dt)
		{

			dt->set_probability((double)1 / (*it)->dependencies()->size());
			dt->child()->add_parent(*it);
		}
	}
}

void ComponentsModel::handle_lru(Node* p_last)
{
	m_lru->erase(std::remove(m_lru->begin(), m_lru->end(), p_last), m_lru->end());
	m_lru->push_back(p_last);
	Node* first = m_lru->front();
    m_lru->pop_front();
	m_lru->push_back(first);

	first->update_component_state();
	first->propagate_state();
}

ComponentsModel::ComponentsModel() : m_root(nullptr)
{
	m_nodes = new list<Node*>();
	m_components = new list<Node*>();
	m_lru = new deque<Node*>();
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

list<Node*> ComponentsModel::find_fault()
{
	list<Node*> path;
	Node* temp = m_root;
	Node* current;
	path.push_back(temp);

	while ((current = temp->get_next()) != nullptr)
	{
		temp = current;
		path.push_back(temp);
	}

	return path;
}


Node* ComponentsModel::root()
{
	return m_root;
}

void ComponentsModel::receive()
{
	for (list<Node*>::iterator it = m_components->begin(); it != m_components->end(); ++it)
	{
		(*it)->receive();
	}

	m_root->receive();
}

list<Node*>* ComponentsModel::components()
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
