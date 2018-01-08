#pragma once

class Node;

class Dependency
{
private:
	Node* m_node;
	double m_probability;
public:
	Dependency(Node* p_child);
	~Dependency();
	Node* child();
	double probability();
	void set_probability(double p_probability);
};
