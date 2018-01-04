#pragma once
#include "Node.h"
#include "CommunicationHandler.h"
#include "CSVReader.h"

class Gps : public Node
{
private:
	enum State
	{
		HEALTHY,
		RECEIVER,
		ANTENNA,
		LOCATION
	};

	double m_x;
	double m_y;
	double m_z;
	int m_seconds;

	CSVReader* m_reader;
	CommunicationHandler* m_communication_handler;

	void create_location_msg(double p_x, double p_y, double p_z, int p_sec);

public:
	Gps(string p_name, Node* p_parent);
	~Gps();

	void update_component_state() override;
};

