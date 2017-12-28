#include "Gps_Ant.h"

Gps_Ant::Gps_Ant(string p_name) : Node(p_name)
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
