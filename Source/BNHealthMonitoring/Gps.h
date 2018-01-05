#pragma once
#include "Node.h"
#include "CommunicationHandler.h"
#include "CSVReader.h"

class Gps : public Node
{
private:
	double m_x;
	double m_y;
	double m_z;
	int m_seconds;
	double m_expected_x;
	double m_expected_y;
	double m_expected_z;

	CSVReader* m_reader;
	CommunicationHandler* m_communication_handler;

	void create_location_msg(double p_x, double p_y, double p_z, int p_sec, double p_delta);
	void notify(int p_state, Node* p_sender) override;

public:
	enum State
	{
		HEALTHY,
		RECEIVER,
		ANTENNA
	};

	Gps(string p_name, Node* p_parent);
	~Gps();

	void update_component_state() override;
	string get_state_str(int p_state) override;

};

