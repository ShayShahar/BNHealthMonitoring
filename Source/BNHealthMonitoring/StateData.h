#pragma once
#include "Externals.h"

class StateData
{
private:
	double m_weight;
	string m_name;
public:
	StateData(double p_weight, string p_name);
	string name();
	double weight();
};
