#include "Link.h"

Link::~Link()
{
}

bool operator==(const Link& p_left, const Link& p_right)
{
	return (p_left.value == p_right.value) && (p_left.parent == p_right.parent) && (p_left.current == p_right.current);
}

bool operator!=(const Link& p_left, const Link& p_right)
{
	return !((p_left.value == p_right.value) && (p_left.parent == p_right.parent) && (p_left.current == p_right.current));
}
