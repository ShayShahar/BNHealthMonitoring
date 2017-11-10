#pragma once

template <class T> class ListItem
{
private:
	T value;
	ListItem<T> *next;

public:
	ListItem(T p_value) : value(p_value){}
	~ListItem(){}
};

