#include "GenericComp.h"
#include "ComponentsModel.h"
#include <iostream>


void main (int argc, char* argv[])
{
	GenericComp *comp1 = new GenericComp("component_1", 3);
	GenericComp *comp2 = new GenericComp("component_2", 3);
	GenericComp *comp3 = new GenericComp("component_3", 3);
	GenericComp *comp4 = new GenericComp("component_4", 3);
	GenericComp *comp5 = new GenericComp("component_5", 3);
	GenericComp *comp6 = new GenericComp("component_6", 3);
	GenericComp *comp7 = new GenericComp("component_7", 3);

	// define comp1 as root
	ComponentsModel *cdm = new ComponentsModel(comp1);

	//probabilities of comp1 for state 0
	comp1->add_link(0, Link(comp1, comp2, 0.9));
	comp1->add_link(0, Link(comp1, comp3, 0.1));

	//probabilities of comp2 for state 0
	comp2->add_link(0, Link(comp2, comp4, 0.1));
	comp2->add_link(0, Link(comp2, comp5, 0.9));

	//probabilities of comp3 for state 0
	comp3->add_link(0, Link(comp3, comp6, 0.1));
	comp3->add_link(0, Link(comp3, comp7, 0.9));

	for (int i = 0; i < 100; i++)
	{
		std::cout << cdm->find_fault()->name()<< std::endl;
	}
	
	int a;
	std::cin >> a;
	
}

