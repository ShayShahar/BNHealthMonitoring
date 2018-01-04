#pragma once
#include "Node.h"
#include "CSVReader.h"

class ACS : public Node
{
private:
	float m_voltage;
	CSVReader* m_reader;
	const float max_voltage = 12.0;

public:
	enum State
	{
		HEALTHY,
		MAGNETORQUER,
		RWX,
		RWY,
		RWZ,
		VOLTAGE
	};

	ACS(string p_name, Node* p_parent);
	~ACS();
	void update_component_state() override;
    string get_state_str(int p_state) override;

};

