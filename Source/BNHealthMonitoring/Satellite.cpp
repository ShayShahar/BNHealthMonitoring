#include "Satellite.h"

Sattelite::Sattelite(string p_name) : Component(p_name)
{
	m_reader = new CSVReader("CSVFiles//OutFileSatAlpha.csv");
	m_communication_handler = CommunicationHandler::get_instance();
}

Sattelite::~Sattelite()
{
	delete m_reader;
}

void Sattelite::update_component_state()
{

}

void Sattelite::receive()
{
	vector<string> data = m_reader->readLine();

	m_seconds = stoi(data[0]);
	m_x = stod(data[3]);
	m_y = stod(data[4]);
	m_z = stod(data[5]);

	double delta = sqrt(pow(m_expected_x - m_x, 2) + pow(m_expected_y - m_y, 2) + pow(m_expected_z - m_z, 2));

	double v_x = stod(data[6]);
	double v_y = stod(data[7]);
	double v_z = stod(data[8]);

	m_expected_x = m_x + 20 * v_x;
	m_expected_y = m_y + 20 * v_y;
	m_expected_z = m_z + 20 * v_z;

	create_location_msg(m_x, m_y, m_z, m_seconds, delta);
}

void Sattelite::create_location_msg(double p_x, double p_y, double p_z, int p_sec, double p_delta)
{
	HealthMonitoringMessages::DataUpdateMsg msg;
	msg.set_opcode(HealthMonitoringMessages::OpCode::SatLocation);

	HealthMonitoringMessages::LocationMessage* data = msg.mutable_location();
	data->set_x(p_x);
	data->set_y(p_y);
	data->set_z(p_z);
	data->set_seconds(p_sec);
	data->set_delta(p_delta);

	m_communication_handler->send(msg);
}
