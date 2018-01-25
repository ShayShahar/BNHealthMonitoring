#pragma once
#include "../BL/CommunicationHandler.h"
#include "../Helpers/CSVReader.h"
#include "../BL/Component.h"

/* Class: Satellite
Reflected satellite component, implements the Component methods.
*/
class Satellite : public Component
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

	Satellite(string p_name);
	~Satellite();

	void update_component_state() override;
	void receive() override;

};
