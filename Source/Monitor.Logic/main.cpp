#include "BL/ComponentsModel.h"
#include "BL/Scheduler.h"

void main (int argc, char* argv[])
{
	cout << "Health Monitoring Started..." << endl;

	Scheduler scheduler;
	scheduler.init();
	scheduler.join();
}

