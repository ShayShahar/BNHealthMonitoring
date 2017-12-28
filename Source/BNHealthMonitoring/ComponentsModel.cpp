#define _CRT_SECURE_NO_WARNINGS

#include "ComponentsModel.h"
#include "Gps.h"
#include "Externals.h"


ComponentsModel::ComponentsModel(Node* root)
{
	system_root = root;
}


ComponentsModel::~ComponentsModel()
{

}

Node * ComponentsModel::find_fault() const
{
	Node* temp = system_root;
	Node* current;
	
	while ((current = temp->get_next()) != nullptr)
	{
		temp = current;
	}

	return temp;
}

void ComponentsModel::publish(HealthMonitoringMessages::DataReplyMsg& p_msg)
{
}
