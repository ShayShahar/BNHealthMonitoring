#include "ComponentsModel.h"
#include "Scheduler.h"

void main (int argc, char* argv[])
{
	cout << "Health Monitoring Started..." << endl;

	Scheduler scheduler;
	scheduler.init();
	scheduler.join();
}

