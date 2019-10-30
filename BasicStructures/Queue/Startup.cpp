#include <iostream>
#include "Queue.h"

using namespace std;

int main()
{
	Queue<int> q;

	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);

	while (!q.Empty())
	{
		cout << q.Front() << ' ';
		q.Pop();
	}

	cout << endl;

	cout << q.Front() << ' ' << q.Back() << endl;

	while (true) {}
	return 0;
}