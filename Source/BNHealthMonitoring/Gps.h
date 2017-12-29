#pragma once
#include "Node.h"
#include "CommunicationHandler.h"
#include "CSVReader.h"

class CGps : public Node
{
private:
	double m_x;
	double m_y;
	double m_z;
	int m_seconds;

	CSVReader* m_reader;
	CommunicationHandler* m_communication_handler;

	void create_location_msg(double p_x, double p_y, double p_z, int p_sec);

public:
	CGps(string p_name);
	~CGps();

	void update_component_state() override;
};

