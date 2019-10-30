#pragma once

template <typename T>
struct Node
{
	T value;
	Node<T>* next;

	Node(const T&);
};

template <typename T>
Node<T>::Node(const T& value)
{
	this->value = value;
	this->next = nullptr;
}