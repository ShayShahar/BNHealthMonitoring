#include "ComponentsModel.h"
#include "Gps.h"


ComponentsModel::ComponentsModel()
{
	system_root = new CGps("root");
}


ComponentsModel::~ComponentsModel()
{
}
