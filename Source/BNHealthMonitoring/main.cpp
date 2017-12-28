#include "GenericComp.h"
#include "ComponentsModel.h"
//#include "MemoryWrapper.h"
#include "Gps.h"
#include "CommunicationHandler.h"

void main (int argc, char* argv[])
{
	//MemoryWrapper* seg = MemoryWrapper::getInstance();
	CGps* gps = new CGps("GPS");
	gps->update_component_state();

	GenericComp *comp1 = new GenericComp("component_1");
	GenericComp *comp2 = new GenericComp("component_2");
	GenericComp *comp3 = new GenericComp("component_3");
	GenericComp *comp4 = new GenericComp("component_4");
	GenericComp *comp5 = new GenericComp("component_5");
	GenericComp *comp6 = new GenericComp("component_6");
	GenericComp *comp7 = new GenericComp("component_7");

	// define comp1 as root
	ComponentsModel* cdm = new ComponentsModel(comp1);



	//probabilities of comp1 for state 0
	comp1->add_link(0, Link(comp1, comp2, 0.9));
	comp1->add_link(0, Link(comp1, comp3, 0.1));

	comp1->add_link(1, Link(comp1, comp2, 0.3));
	comp1->add_link(1, Link(comp1, comp3, 0.7));

	//probabilities of comp2 for state 0
	comp2->add_link(0, Link(comp2, comp4, 0.1));
	comp2->add_link(0, Link(comp2, comp5, 0.9));

	//probabilities of comp3 for state 0
	comp3->add_link(0, Link(comp3, comp6, 0.1));
	comp3->add_link(0, Link(comp3, comp7, 0.9));

	CommunicationHandler commHandler(*cdm);
	commHandler.init();
	
	int c4 = 0, c5 = 0, c6 = 0, c7 = 0;

	for (int i = 0; i < 100; i++)
	{
		Node* component = cdm->find_fault();
		std::cout << component->name() << std::endl;
	
		if (component->name() == "component_4")
		{
			c4++;
		}
		else if (component->name() == "component_5")
		{
			c5++;
		}
		else if (component->name() == "component_6")
		{
			c6++;
		}
		else if (component->name() == "component_7")
		{
			c7++;
		}
	}
	
	int sum = c4 + c5 + c6 + c7;
	std::cout << "component 4: " << (float)c4 / sum * 100 << std::endl;
	std::cout << "component 5: " << (float)c5 / sum * 100 << std::endl;
	std::cout << "component 6: " << (float)c6 / sum * 100 << std::endl;
	std::cout << "component 7: " << (float)c7 / sum * 100 << std::endl;


	commHandler.join();

	int a;
	std::cin >> a;
	
}

