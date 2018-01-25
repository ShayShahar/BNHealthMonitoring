#pragma once
#include "../Helpers/CSVReader.h"
#include "../BL/Component.h"

/* Class: ACS
   Reflected ACS component, implements the Component methods.
*/
class ACS : public Component
{
private:
	float m_voltage;
	CSVReader* m_reader;
	const float max_voltage = 12.0;

public:
	ACS(string p_name);
	~ACS();
	void update_component_state() override;
	void receive() override;
};

