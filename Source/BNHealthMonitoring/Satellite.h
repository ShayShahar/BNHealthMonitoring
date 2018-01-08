#pragma once
#include "Node.h"
#include "CommunicationHandler.h"
#include "CSVReader.h"

class Sattelite : public Node
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

public:
	enum State
	{
		HEALTHY,
		ACS,
		EPS,
		GPS
	};

	Sattelite(string p_name);
	~Sattelite();

	void update_component_state() override;
	string get_state_str(int p_state) override;
};
