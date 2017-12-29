#include "GpsReceiver.h"

GpsReceiver::GpsReceiver(string p_name) : Node(p_name)
{
	m_reader = new CSVReader("CSVFiles//GpsReceiver.csv");
}

GpsReceiver::~GpsReceiver()
{
	delete m_reader;
}

void GpsReceiver::update_component_state()
{
	vector<string> data = m_reader->readLine();

	temperature = stod(data[0]);
	shock = stod(data[1]);
	voltage = stod(data[2]);

}
