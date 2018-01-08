#include "Satellite.h"

void Sattelite::notify(int p_state, Node* p_sender)
{
	if (p_state == 0)
		m_state = State::HEALTHY;

	else if (p_sender->name() == "ACS")
		m_state = State::ACS;

	else if (p_sender->name() == "EPS")
		m_state = State::EPS;

	else if (p_sender->name() == "GPS")
		m_state = State::GPS;

	if (m_parent != nullptr)
		m_parent->notify(m_state, this);
}

Sattelite::Sattelite(string p_name) : Node(p_name)
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

string Sattelite::get_state_str(int p_state)
{
	switch (p_state)
	{
		case State::ACS:
			return "ACS";
		case State::EPS:
			return "EPS";	
		case State::GPS:
			return "GPS";
	}

	return "HEALTHY";
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
