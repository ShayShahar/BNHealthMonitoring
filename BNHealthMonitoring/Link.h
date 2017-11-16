#pragma once
class Node;

class Link
{
public:
	Link(Node* p_c1, Node* p_c2, double p_value) : current(p_c1), parent(p_c2), value(p_value){}

	~Link();

	Node* current;
	Node* parent;
	double value;
};

bool operator==(const Link& p_left, const Link& p_right);
bool operator!=(const Link& p_left, const Link& p_right);


