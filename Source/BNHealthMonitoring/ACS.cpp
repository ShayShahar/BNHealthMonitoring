#include "ACS.h"

ACS::ACS(string p_name) : Node(p_name), m_voltage(0)
{
	m_reader = new CSVReader("CSVFiles//ACS.csv");
}

ACS::~ACS()
{
	delete m_reader;
}
void ACS::update_component_state()
{
	vector<string> data = m_reader->readLine();

	m_voltage = stod(data[0]);

}

string ACS::get_state_str(int p_state)
{
	switch (p_state)
	{
		case State::MAGNETORQUER:
			return "MAGNETORQUER";
		case State::RWX:
			return "RWX";		
		case State::RWY:
			return "RWY";		
		case State::RWZ:
			return "RWZ";	
	}

	return "HEALTHY";
}
