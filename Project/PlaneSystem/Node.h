#include "Plane.h"

struct Node
{
	Plane value;
	Node* left;
	Node* right;

	Node(const Plane& planeValue) : value(planeValue)
	{
		left = right = nullptr;
	}

	bool HasLeft() const
	{
		return left != nullptr;
	}

	bool HasRight() const
	{
		return right != nullptr;
	}
};