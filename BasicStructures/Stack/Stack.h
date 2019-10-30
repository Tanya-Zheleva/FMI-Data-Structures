#pragma once
#include <iostream>
#include "Node.h"

template <typename T>
class Stack
{
private:
	Node<T>* first;
	int size;

public:
	Stack();
	Stack(const Stack<T>&);
	Stack<T>& operator=(const Stack<T>&);
	~Stack();

	void CopyFrom(const Stack<T>&);
	void Free();

	void Push(const T&);
	T& Top() const;
	void Pop();

	bool Empty() const;
	int Size() const;
};

template <typename T>
void Stack<T>::Free()
{
	while (!Empty())
	{
		Pop();
	}
}

template <typename T>
void Stack<T>::CopyFrom(const Stack<T>& other)
{
	Node<T>* temp = other.first;

	while (temp != nullptr)
	{
		Push(temp->value);
		temp = temp->next;
	}
}

template <typename T>
Stack<T>::Stack()
{
	size = 0;
	first = nullptr;
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other)
{
	CopyFrom(other);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}

	return *this;
}

template <typename T>
Stack<T>::~Stack()
{
	Free();
}

template <typename T>
void Stack<T>::Push(const T& value)
{
	Node<T>* temp = new Node<T>(value);

	temp->next = first;
	first = temp;

	size++;
}

template <typename T>
T& Stack<T>::Top() const
{
	return first->value;
}

template <typename T>
void Stack<T>::Pop()
{
	if (size == 0)
	{
		throw std::logic_error("Stack is empty");
	}

	Node<T>* current = first;

	first = first->next;
	delete current;

	size--;
}

template <typename T>
bool Stack<T>::Empty() const
{
	return size == 0;
}

template <typename T>
int Stack<T>::Size() const
{
	return size;
}