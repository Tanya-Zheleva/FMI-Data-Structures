#include "Node.h"
#pragma once

template <typename T>
class Queue
{
private:
	int size;
	Node<T>* front;
	Node<T>* back;

	void Copy(const Queue<T>&);
	void Delete();

public:
	Queue();
	Queue(const Queue<T>&);
	Queue<T>& operator=(const Queue<T>&);
	~Queue();

	T& Front() const;
	T& Back() const;
	void Push(const T&);
	void Pop();
	bool Empty() const;
	int Size() const;
};

template <typename T>
Queue<T>::Queue()
{
	size = 0;
	front = nullptr;
	back = nullptr;
}

template <typename T>
Queue<T>::Queue(const Queue<T>& other)
{
	Copy(other);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
	if (this != &other)
	{
		Delete();
		Copy(other);
	}

	return *this;
}

template <typename T>
Queue<T>::~Queue()
{
	Delete();
}

template <typename T>
void Queue<T>::Copy(const Queue<T>& other)
{
	Node<T>* temp = other.front;

	while (temp != nullptr)
	{
		Push(temp->value);
		temp = temp->next;
	}
}

template <typename T>
void Queue<T>::Delete()
{
	while (!Empty())
	{
		Pop();
	}
}

template <typename T>
void Queue<T>::Push(const T& value)
{
	Node<T>* newValue = new Node<T>(value);

	if (size == 0)
	{
		front = back = newValue;
	}
	else
	{
		back->next = newValue;
		back = newValue;
	}

	size++;
}

template <typename T>
void Queue<T>::Pop()
{
	if (size == 0)
	{
		throw std::logic_error("Queue is empty");
	}

	Node<T>* temp = front;
	front = front->next;
	delete temp;

	size--;
}

template <typename T>
bool Queue<T>::Empty() const
{
	return size == 0;
}

template <typename T>
int Queue<T>::Size() const
{
	return size;
}

template <typename T>
T& Queue<T>::Front() const
{
	return front->value;
}

template <typename T>
T& Queue<T>::Back() const
{
	return back->value;
}