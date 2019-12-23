#include <iostream>
#include <string>

using namespace std;

class SinglyLinkedListNode 
{
public:
	int data;
	SinglyLinkedListNode *next;

	SinglyLinkedListNode(int node_data) 
	{
		this->data = node_data;
		this->next = nullptr;
	}
};

class SinglyLinkedList
{
public:
	SinglyLinkedListNode *head;
	SinglyLinkedListNode *tail;

	SinglyLinkedList() 
	{
		this->head = nullptr;
		this->tail = nullptr;
	}

	void InsertNode(int data) 
	{
		SinglyLinkedListNode* node = new SinglyLinkedListNode(data);

		if (!this->head) 
		{
			this->head = node;
		}
		else
		{
			this->tail->next = node;
		}

		this->tail = node;
	}
};

void PrintList(SinglyLinkedListNode* node, string sep) 
{
	while (node) 
	{
		cout << node->data;
		node = node->next;

		if (node) cout << sep;
	}
}

void FreeList(SinglyLinkedListNode* node) 
{
	while (node) 
	{
		SinglyLinkedListNode* temp = node;
		node = node->next;

		free(temp);
	}
}

SinglyLinkedListNode* RemoveDuplicates(SinglyLinkedListNode* head)
{
	if (!head->next) return head;

	SinglyLinkedListNode* temp = head;

	while (temp) 
	{
		if (temp->next && temp->data == temp->next->data) {
			temp->next = temp->next->next;
		}
		else 
		{
			temp = temp->next;
		}
	}

	return head;
}

int main()
{
	int t = 0;
	cin >> t;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int t_itr = 0; t_itr < t; t_itr++) 
	{
		SinglyLinkedList* list = new SinglyLinkedList();

		int count = 0;
		cin >> count;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		for (int i = 0; i < count; i++) 
		{
			int item = 0;
			cin >> item;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			list->InsertNode(item);
		}

		SinglyLinkedListNode* updatedList = RemoveDuplicates(list->head);

		PrintList(updatedList, " ");
		cout << "\n";

		FreeList(updatedList);
	}

	while (true) { }
	return 0;
}
