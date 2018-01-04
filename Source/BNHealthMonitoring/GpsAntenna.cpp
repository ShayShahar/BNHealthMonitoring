#include "GpsAntenna.h"

GpsAntenna::GpsAntenna(string p_name, Node* p_parent) : Node(p_name, p_parent), m_tempature(0), m_vibration(0), m_altitude(0)
{
	m_reader = new CSVReader("CSVFiles//Gps_Ant.csv");
}

GpsAntenna::~GpsAntenna()
{
	delete m_reader;
}

void GpsAntenna::update_component_state()
{
	vector<string> data = m_reader->readLine();

	m_tempature = stod(data[0]);
	m_vibration = stod(data[1]);
	m_altitude = stod(data[2]);

}
