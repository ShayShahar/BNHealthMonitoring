#pragma once
#include "../Helpers/CSVReader.h"
#include "../BL/Component.h"


/* Class: GPS
Reflected GPS component, implements the Component methods.
*/
class Gps : public Component
{
public:

	Gps(string p_name);
	~Gps();

	void update_component_state() override;
	void receive() override;
};

