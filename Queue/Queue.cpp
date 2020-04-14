#include <iostream>
#pragma once
#include <exception>

using namespace std;
template <typename T>
class queue
{
private:
	typedef struct unit
	{
		T value;
		unit* next;
		unit(T, unit*);
		unit(T);
	} unit;

	unit* head;

	int maxCount;

public:
	//Constructors
	queue(int);
	queue(T[]);
	queue( queue&);
	//Destructor
	~queue();
	//Return Methods
	T front();
	T back();
	//Properties
	bool empty();
	int size();
	int GetMaxCount();
	void resize(int);
	//Add/Pop Methods
	void pop();
	void push(T);
	void push(T[]);
	void push( queue&);
	//Merging
	queue<T> merge( queue&) ;
};



int main()
{
	
}

template <typename T>
queue<T>::unit::unit(T value)
{
	this->value = value;
	this->next = NULL;
}

template <typename T>
queue<T>::unit::unit(T value, unit* next)
{
	this->value = value;
	this->next = next;
}

template <typename T>
queue<T>::queue( int maxCount)
{
	this->head = NULL;
	this->maxCount = maxCount;
}

template <typename T>
queue<T>::queue(T values[])
{
	head = NULL;
	maxCount = sizeof(values) / sizeof(T);
	push(values);
}

template <typename T>
queue<T>::queue(queue& object)
{
	head = NULL;
	maxCount = object.max_capacity;
	push(object);
}
template <typename T>
queue<T>::~queue()
{
	unit* current = head;
	while (current != NULL)
	{
		unit* next = current->next;
		delete current;
		current = next;
	}
	head = NULL;
}

template <typename T>
T queue<T>::front()
{
	return head->value;
}

template <typename T>
T queue<T>::back()
{
	unit* current = head;
	while (current->next != NULL)
		current = current->next;
	return current->value;
}

template <typename T>
bool queue<T>::empty()
{
	if (head == nullptr) return true;
	return false;
}

template <typename T>
int queue<T>::size()
{
	int counter = 0;
	unit* current = head;
	while (current != nullptr)
	{
		counter++;
		current = current->next;
	}
	return counter;
}

template <typename T>
int queue<T>::GetMaxCount()
{
	return maxCount;
}

template <typename T>
void queue<T>::resize( int newSize)
{
	if (newSize < size())
		throw exception("This method is pointless in this case");
	maxCount = newSize;
}


template <typename T>
void queue<T>::push(T value)
{
	if (size() == maxCount)
		throw exception("Error. Maximum capacity exceeded.");
	unit* temp = new unit(value);
	if (empty())
	{
		head = temp;
		return;
	}
	unit* current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = temp;
}

template <typename T>
void queue<T>::push(T values[])
{
	if (size() + sizeof(values) / sizeof(T) > maxCount)
		throw exception("Queue is full");
	for (T value : values)
		push(value);
}

template <typename T>
void queue<T>::push( queue& object)
{
	if (size() + object.size() > maxCount)
		throw exception("Queue is full");
	unit* current = object.head;
	while (current != NULL)
	{
		push(current->value);
		current = current->next;
	}
}

template <typename T>
queue<T> queue<T>::merge( queue& object) 
{
	queue<T> tempQueue(maxCount + object.maxCount);
	tempQueue.push(*this);
	tempQueue.push(object);
	return tempQueue;
}


template <typename T>
void queue<T>::pop()
{
	if (empty())
		throw exception("Queue is empty.");
	unit* tempHead = head;
	head = head->next;
	delete tempHead;
}