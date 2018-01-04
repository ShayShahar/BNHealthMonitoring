#include "GpsAntenna.h"

void GpsAntenna::notify(int p_state, Node* p_sender)
{
}

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

string GpsAntenna::get_state_str(int p_state)
{
	switch (p_state)
	{
	case State::TEMPERATURE:
		return "TEMPERATURE";
	case State::ALTITUDE:
		return "ALTITUDE";
	case State::VIBRATION:
		return "VIBRATION";
	}

	return "HEALTHY";
}
