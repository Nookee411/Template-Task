#pragma once
#include <exception>
template <typename T>
class queue
{
private:
	typedef struct node
	{
		T value;
		node* next;
		node(T);
		node(T, node*);
	} node;
	node* head;
	int maxCount;
public:
	queue(int);
	queue(T[]);
	queue(const queue&);
	~queue();

	T front() const;
	T back() const;

	bool empty() const;
	int size() const;
	int max_capacity() const;
	void resize(int);

	void push(T);
	void push(T[]);
	void push(const queue&);
	void pop();

	queue<T> merge(const queue&) const;
};

template <typename T>
queue<T>::node::node(T value)
{
	this->value = value;
	this->next = NULL;
}

template <typename T>
queue<T>::node::node(T value, node* next)
{
	this->value = value;
	this->next = next;
}


template <typename T>
queue<T>::queue(const int maxCount)
{
	this->head = null;
	this->maxCount = maxCount;
}

template <typename T>
queue<T>::queue(T values[])
{
	head = null;
	maxCount = sizeof(values) / sizeof(T);
	push(values);
}

template <typename T>
queue<T>::queue(const queue& object) : head_(nullptr)
{
	head = NULL;
	maxCount= object.max_capacity;
	push(object);
}

template <typename T>
queue<T>::~queue()
{
	node* current = head_;
	while (current != nullptr)
	{
		node* next = current->next;
		delete current;
		current = next;
	}
	head_ = nullptr;
}

template <typename T>
T queue<T>::front() const
{
	return head_->value;
}

template <typename T>
T queue<T>::back() const
{
	node* current = head_;
	while (current->next != nullptr)
		current = current->next;
	return current->value;
}

template <typename T>
bool queue<T>::empty() const
{
	if (head_ == nullptr) return true;
	return false;
}

template <typename T>
int queue<T>::size() const
{
	auto counter = 0;
	node* current = head_;
	while (current != nullptr)
	{
		counter++;
		current = current->next;
	}
	return counter;
}

template <typename T>
int queue<T>::max_capacity() const
{
	return max_capacity_;
}

template <typename T>
void queue<T>::resize(const int new_size)
{
	if (new_size < size())
		throw std::exception("Error. New max size can't be lesser that current number of elements.");
	max_capacity_ = new_size;
}


template <typename T>
void queue<T>::push(T value)
{
	if (size() == max_capacity_)
		throw std::exception("Error. Maximum capacity exceeded.");
	node* new_node = new node(value);
	if (empty())
	{
		head_ = new_node;
		return;
	}
	node* current = head_;
	while (current->next != nullptr)
		current = current->next;
	current->next = new_node;
}

template <typename T>
void queue<T>::push(T values[])
{
	if (size() + sizeof(values) / sizeof(T) > max_capacity_)
		throw std::exception("Error. Not enough capacity.");
	for (T value : values)
		push(value);
}

template <typename T>
void queue<T>::push(const queue& other)
{
	if (size() + other.size() > max_capacity_)
		throw std::exception("Error. Not enough capacity.");
	node* current = other.head_;
	while (current != nullptr)
	{
		push(current->value);
		current = current->next;
	}
}

template <typename T>
queue<T> queue<T>::merge(const queue& other) const
{
	queue<T> new_queue(max_capacity_ + other.max_capacity_);
	new_queue.push(*this);
	new_queue.push(other);
	return new_queue;
}


template <typename T>
void queue<T>::pop()
{
	if (empty())
		throw std::exception("Error. Queue is empty.");
	node* tempHead = head;
	head = head->next;
	delete tempHead;
}