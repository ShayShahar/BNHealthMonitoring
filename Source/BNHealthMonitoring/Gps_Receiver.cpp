#include "Gps_Receiver.h"



Gps_Receiver::Gps_Receiver(const char* p_name, unsigned int p_nStates)
{
	m_reader = new CSVReader("C:\\Users\\shays\\Desktop\\OutFileSatAlpha.csv");
}


Gps_Receiver::~Gps_Receiver()
{
	delete m_reader;
}

void Gps_Receiver::update_component_state()
{

}
