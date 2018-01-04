#include "ComponentsModel.h"

ComponentsModel::ComponentsModel(): m_root(nullptr)
{
	m_components = new list<Node*>();
	m_leafs = new list<Node*>();
}

ComponentsModel::~ComponentsModel()
{
	delete m_leafs;
	delete m_components;
}

void ComponentsModel::init()
{
	Sattelite* satellite = new Sattelite("Satellite Alpha", nullptr);

	Gps* gps = new Gps("GPS", satellite);
	ACS* acs = new ACS("ACS", satellite);
	EPS* eps = new EPS("EPS", satellite);

	Magnetorquer* magnetorquer = new Magnetorquer("Magnetorquer", acs);
	ReactionWeel* rwx = new ReactionWeel("RWX", acs);
	ReactionWeel* rwy = new ReactionWeel("RWY", acs);
	ReactionWeel* rwz = new ReactionWeel("RWZ", acs);

	GpsReceiver* gps_receiver = new GpsReceiver("GPS Receiver", gps);
	GpsAntenna* gps_antenna = new GpsAntenna("GPS Antenna", gps);

	//m_components->push_back(satellite);
	m_components->push_back(gps);
	//m_components->push_back(acs);
	//m_components->push_back(eps);
	//m_components->push_back(magnetorquer);
	//m_components->push_back(rwx);
	//m_components->push_back(rwy);
	//m_components->push_back(rwz);
	//m_components->push_back(gps_receiver);
	//m_components->push_back(gps_antenna);

	m_leafs->push_back(magnetorquer);
	m_leafs->push_back(rwx);
	m_leafs->push_back(rwz);
	m_leafs->push_back(rwy);
	m_leafs->push_back(gps_receiver);
	m_leafs->push_back(gps_antenna);
	m_leafs->push_back(gps_antenna);
	m_leafs->push_back(eps);

	m_root = satellite;

	satellite->add_link(Sattelite::State::HEALTHY, Link(satellite, gps, 0.05));
	satellite->add_link(Sattelite::State::HEALTHY, Link(satellite, acs, 0.05));
	satellite->add_link(Sattelite::State::HEALTHY, Link(satellite, eps, 0.05));

	//satellite->add_link(1, Link(satellite, gps, 0.2));
	//satellite->add_link(1, Link(satellite, comp2, 0.1));
	//satellite->add_link(1, Link(satellite, comp3, 0.7));

	////probabilities of comp2 for state 0
	//comp2->add_link(0, Link(comp2, comp4, 0.1));
	//comp2->add_link(0, Link(comp2, comp5, 0.9));

	////probabilities of comp3 for state 0
	//comp3->add_link(0, Link(comp3, comp6, 0.1));
	//comp3->add_link(0, Link(comp3, comp7, 0.9));
}

void ComponentsModel::propagate_states()
{
	for (list<Node*>::iterator it = m_leafs->begin(); it != m_leafs->end(); ++it)
	{
		(*it)->propagate_state();
	}
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

void ComponentsModel::update()
{
	for (list<Node*>::iterator it = m_components->begin(); it != m_components->end(); ++it)
	{
		(*it)->update_component_state();
	}
}

Node* ComponentsModel::root()
{
	return m_root;
}

void ComponentsModel::get_cdm_data(HealthMonitoringMessages::DataUpdateMsg& p_msg)
{
	p_msg.set_opcode(HealthMonitoringMessages::OpCode::Components);
	HealthMonitoringMessages::CDMMessage *cdmMsg = p_msg.mutable_components();
	HealthMonitoringMessages::pComponent *root = cdmMsg->mutable_cdm_root();
	m_root->get_data(root);
}
