#pragma once

template <class T> class ListItem
{

public:
	ListItem(T p_value) : value(p_value){}
	~ListItem(){}

	T value;
	ListItem<T> *next;
};

template <class T>
bool operator==(const ListItem<T>& p_left, const ListItem<T>& p_right)
{
	return p_left.value == p_right.value && p_left.next == p_right.next;
}

template <class T>
bool operator!=(const ListItem<T>& p_left, const ListItem<T>& p_right)
{
	return !(p_left.value == p_right.value && p_left.next == p_right.next);
}
