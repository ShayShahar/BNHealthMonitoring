#include "Gps.h"

Gps::Gps(string p_name, Node* p_parent) : Node(p_name, p_parent)
{
	m_reader = new CSVReader("CSVFiles//OutFileSatAlpha.csv");
	m_communication_handler = CommunicationHandler::get_instance();
}

Gps::~Gps()
{
	delete m_reader;
}

void Gps::update_component_state()
{
	vector<string> data = m_reader->readLine();

	m_seconds = stoi(data[0]);
	m_x = stod(data[3]);
	m_y = stod(data[4]);
	m_z = stod(data[5]);

	double v_x = stod(data[6]);
	double v_y = stod(data[7]);
	double v_z = stod(data[8]);

	create_location_msg(m_x, m_y, m_z, m_seconds);
}

string Gps::get_state_str(int p_state)
{
	switch (p_state)
	{
		case State::ANTENNA:
			return "ANTENNA";
		case State::LOCATION:
			return "LOCATION";
		case State::RECEIVER:
			return "RECEIVER";
	}

	return "HEALTHY";
}

void Gps::create_location_msg(double p_x, double p_y, double p_z, int p_sec)
{
	HealthMonitoringMessages::DataUpdateMsg msg;
	msg.set_opcode(HealthMonitoringMessages::OpCode::SatLocation);

	HealthMonitoringMessages::LocationMessage* data = msg.mutable_location();
	data->set_x(p_x);
	data->set_y(p_y);
	data->set_z(p_z);
	data->set_seconds(p_sec);

	m_communication_handler->send(msg);
}

void Gps::notify(int p_state, Node* p_sender)
{
	if (p_state == 0)
		m_state = State::HEALTHY;

	else if (p_sender->name() == "GPS Receiver")
		m_state = State::RECEIVER;

	else if (p_sender->name() == "GPS Antenna")
		m_state = State::ANTENNA;

	if (m_parent != nullptr)
		m_parent->notify(m_state, this);
}

//void CGps::update_component_state()
//{
//	//m_px = m_x;
//	//m_py = m_y;
//	//m_pz = m_z;
//
//	//m_x = (segment->mem_seg[m_xOffset] << 24) | (segment->mem_seg[m_xOffset + 1] << 16) | (segment->mem_seg[m_xOffset + 2] << 8) | segment->mem_seg[m_xOffset + 3];
//	//m_y = (segment->mem_seg[m_yOffset] << 24) | (segment->mem_seg[m_yOffset + 1] << 16) | (segment->mem_seg[m_yOffset + 2] << 8) | segment->mem_seg[m_yOffset + 3];
//	//m_z = (segment->mem_seg[m_zOffset] << 24) | (segment->mem_seg[m_zOffset + 1] << 16) | (segment->mem_seg[m_zOffset + 2] << 8) | segment->mem_seg[m_zOffset + 3];
//
//}
//
