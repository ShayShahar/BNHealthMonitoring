#include "Gps_Ant.h"

Gps_Ant::Gps_Ant(const char* p_name, unsigned int p_nStates) : Node(p_name, p_nStates)
{
	m_reader = new CSVReader("C:\\Users\\Yakir\\Desktop\\Gps_Ant.csv");
}

Gps_Ant::~Gps_Ant()
{
	delete m_reader;
}

void Gps_Ant::update_component_state()
{
	vector<string> data = m_reader->readLine();

	tempature = stod(data[0]);
	vibration = stod(data[1]);
	altitude = stod(data[2]);

}
