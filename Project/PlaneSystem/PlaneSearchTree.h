#include "Node.h"

Plane EMPTY_PLANE = { 0, "NULL", "NULL", 0 };

class PlaneSearchTree
{
private:
	Node* root;

	void DeleteNode(Node*);
	void InsertNode(Node*&, const Plane&);
	Plane& FindNode(Node*, int);
	bool ContainsNode(Node*, int);
	void InOrder(Node*);

public:
	PlaneSearchTree();
	~PlaneSearchTree();

	void Reset();

	Plane& Find(int);
	void Insert(const Plane&);
	bool Contains(int);
	void Clear();
	void Print();
};

void PlaneSearchTree::DeleteNode(Node* node)
{
	if (node->HasLeft()) {
		DeleteNode(node->left);
	}

	if (node->HasRight()) {
		DeleteNode(node->right);
	}

	delete node;
}

void PlaneSearchTree::InsertNode(Node*& node, const Plane& value)
{
	if (!node) {
		node = new Node(value);
	}
	else
	{
		value > node->value ?
			InsertNode(node->right, value) :
			InsertNode(node->left, value);
	}
}

Plane& PlaneSearchTree::FindNode(Node* node, int id)
{
	if (!node) return EMPTY_PLANE;

	if (id == node->value.GetId()) return node->value;

	if (id < node->value.GetId()) return FindNode(node->left, id);

	return FindNode(node->right, id);
}

bool PlaneSearchTree::ContainsNode(Node* node, int id)
{
	if (!node) return false;

	if (id == node->value.GetId()) return true;

	if (id < node->value.GetId()) return ContainsNode(node->left, id);

	return ContainsNode(node->right, id);
}

PlaneSearchTree::PlaneSearchTree()
{
	root = nullptr;
}

PlaneSearchTree::~PlaneSearchTree()
{
	Clear();
}

void PlaneSearchTree::Insert(const Plane& value)
{
	InsertNode(root, value);
}

Plane& PlaneSearchTree::Find(int id)
{
	return FindNode(root, id);
}

bool PlaneSearchTree::Contains(int id)
{
	return ContainsNode(root, id);
}

void PlaneSearchTree::Clear()
{
	DeleteNode(root);
}

void PlaneSearchTree::Print()
{
	InOrder(root);
}

void PlaneSearchTree::InOrder(Node* node)
{
	if (!node) return;

	InOrder(node->left);

	cout << node->value;

	InOrder(node->right);
}

void PlaneSearchTree::Reset()
{
	root = nullptr;
}