#include "Gps.h"

CGps::CGps(const char* p_name, unsigned int p_nStates) : Node(p_name, p_nStates)
{
}


CGps::~CGps()
{
}

void CGps::update_component_state()
{
	m_px = m_x;
	m_py = m_y;
	m_pz = m_z;

	m_x = (segment->mem_seg[m_xOffset] << 24) | (segment->mem_seg[m_xOffset + 1] << 16) | (segment->mem_seg[m_xOffset + 2] << 8) | segment->mem_seg[m_xOffset + 3];
	m_y = (segment->mem_seg[m_yOffset] << 24) | (segment->mem_seg[m_yOffset + 1] << 16) | (segment->mem_seg[m_yOffset + 2] << 8) | segment->mem_seg[m_yOffset + 3];
	m_z = (segment->mem_seg[m_zOffset] << 24) | (segment->mem_seg[m_zOffset + 1] << 16) | (segment->mem_seg[m_zOffset + 2] << 8) | segment->mem_seg[m_zOffset + 3];

	//todo: diff
}

