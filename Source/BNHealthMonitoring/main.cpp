#include "GenericComp.h"
#include "ComponentsModel.h"
#include "Scheduler.h"

void main (int argc, char* argv[])
{
	cout << "Health Monitoring Started..." << endl;

	Scheduler scheduler;
	scheduler.init();
	scheduler.join();


	//
	//int c4 = 0, c5 = 0, c6 = 0, c7 = 0;

	//for (int i = 0; i < 100; i++)
	//{
	//	Node* component = cdm->find_fault();
	//	std::cout << component->name() << std::endl;
	//
	//	if (component->name() == "component_4")
	//	{
	//		c4++;
	//	}
	//	else if (component->name() == "component_5")
	//	{
	//		c5++;
	//	}
	//	else if (component->name() == "component_6")
	//	{
	//		c6++;
	//	}
	//	else if (component->name() == "component_7")
	//	{
	//		c7++;
	//	}
	//}
	//
	//int sum = c4 + c5 + c6 + c7;
	//std::cout << "component 4: " << (float)c4 / sum * 100 << std::endl;
	//std::cout << "component 5: " << (float)c5 / sum * 100 << std::endl;
	//std::cout << "component 6: " << (float)c6 / sum * 100 << std::endl;
	//std::cout << "component 7: " << (float)c7 / sum * 100 << std::endl;

	//int a;
	//std::cin >> a;
}

