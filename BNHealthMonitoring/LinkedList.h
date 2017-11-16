#pragma once
#include "ListItem.h"

template <class T> class LinkedList
{
private:
	unsigned int size;
	ListItem<T>* values;
	ListItem<T>* head;
	ListItem<T>* tail;

public:
	LinkedList();

	~LinkedList(){}

	void add(T p_value);
	void remove(T p_value);
	bool contains(T p_value);
	void clear();
	ListItem<T> first();
	ListItem<T> end();
};

template <class T>
LinkedList<T>::LinkedList()
{
	size = 0;
	values = nullptr;
}

template <class T>
void LinkedList<T>::add(T p_value)
{
	ListItem<T> *item = new ListItem<T>(p_value);
	size++;

	if (head == nullptr)
	{
		tail = item;
		head = item;
	}
	else
	{
		tail->next = item;
		tail = item;
	}
}

template <class T>
void LinkedList<T>::remove(T p_value)
{
	if (head->value == p_value)
	{
		ListItem<T> temp = head->next;
		delete head;
		head = temp;
		size--;
		return;
	}
	 //not implemented yet
}

template <class T>
bool LinkedList<T>::contains(T p_value)
{
	ListItem<T> *curr = this;
	while (curr->next != nullptr)
	{
		if (curr->value == p_value)
			return true;
	
		curr = curr->next;
	}

	return false;
}

template <class T>
void LinkedList<T>::clear()
{
	ListItem<T> *curr = head;
	ListItem<T> *next;

	while (curr != nullptr)
	{
		next = curr->next;
		delete curr;
		curr = next;
	}

	size = 0;
	values = nullptr;
}

template <class T>
ListItem<T> LinkedList<T>::first()
{
	return *head;
}

template <class T>
ListItem<T> LinkedList<T>::end()
{
	return *tail;
}
