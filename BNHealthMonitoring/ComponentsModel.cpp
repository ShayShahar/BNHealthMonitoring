#include "ComponentsModel.h"
#include "Gps.h"


ComponentsModel::ComponentsModel(Node * root)
{
	system_root = root;
}


ComponentsModel::~ComponentsModel()
{
}

Node * ComponentsModel::find_fault()
{
	Node* temp = system_root;
	Node* current;
	
	while ((current = temp->get_next()) != nullptr)
	{
		temp = current;
	}

	return temp;
}
