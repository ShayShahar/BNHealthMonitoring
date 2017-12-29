#include "ComponentsModel.h"

ComponentsModel::ComponentsModel()
{
	m_components = new list<Node*>();
}


ComponentsModel::~ComponentsModel()
{
	delete m_components;
}

void ComponentsModel::init()
{
	GenericComp *satellite = new GenericComp("satellite alpha");
	CGps* gps = new CGps("GPS");
	GenericComp *comp2 = new GenericComp("component_2");
	GenericComp *comp3 = new GenericComp("component_3");
	GenericComp *comp4 = new GenericComp("component_4");
	GenericComp *comp5 = new GenericComp("component_5");
	GenericComp *comp6 = new GenericComp("component_6");
	GenericComp *comp7 = new GenericComp("component_7");

	m_components->push_back(satellite);
	m_components->push_back(gps);
	m_components->push_back(comp2);
	m_components->push_back(comp3);
	m_components->push_back(comp4);
	m_components->push_back(comp5);
	m_components->push_back(comp6);
	m_components->push_back(comp7);

	m_root = satellite;

	//probabilities of comp1 for state 0
	satellite->add_link(0, Link(satellite, gps, 0.1));
	satellite->add_link(0, Link(satellite, comp2, 0.8));
	satellite->add_link(0, Link(satellite, comp3, 0.1));

	satellite->add_link(1, Link(satellite, gps, 0.2));
	satellite->add_link(1, Link(satellite, comp2, 0.1));
	satellite->add_link(1, Link(satellite, comp3, 0.7));

	//probabilities of comp2 for state 0
	comp2->add_link(0, Link(comp2, comp4, 0.1));
	comp2->add_link(0, Link(comp2, comp5, 0.9));

	//probabilities of comp3 for state 0
	comp3->add_link(0, Link(comp3, comp6, 0.1));
	comp3->add_link(0, Link(comp3, comp7, 0.9));
}

Node * ComponentsModel::find_fault()
{
	Node* temp = m_root;
	Node* current;
	
	while ((current = temp->get_next()) != nullptr)
	{
		temp = current;
	}

	return temp;
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
