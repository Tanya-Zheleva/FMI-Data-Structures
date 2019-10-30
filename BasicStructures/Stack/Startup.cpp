#include <iostream>
#include "Stack.h"

using namespace std;

int main()
{
	Stack<int> stack;

	stack.Push(5);
	stack.Push(10);
	stack.Push(15);
	stack.Push(20);

	Stack<int> stack2;

	stack2.Push(1);
	stack2.Push(2);
	stack2.Push(3);
	stack2.Push(4);

	stack = stack2;

	while (!stack.Empty())
	{
		cout << stack.Top() << ' ';
		stack.Pop();
	}

	cout << endl;

	while (true) {}
	return 0;
}