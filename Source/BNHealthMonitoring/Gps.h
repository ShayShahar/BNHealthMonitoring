#pragma once
#include "Node.h"
#include "CSVReader.h"

class CGps : public Node
{
private:
	float m_x;
	float m_y;
	float m_z;
	float m_px;
	float m_py;
	float m_pz;
	const int m_xOffset = 100;
	const int m_yOffset = 104;
	const int m_zOffset = 108;

	CSVReader* m_reader;
	
public:
	CGps(const char* p_name, unsigned int p_nStates);
	~CGps();

	void update_component_state() override;
};

