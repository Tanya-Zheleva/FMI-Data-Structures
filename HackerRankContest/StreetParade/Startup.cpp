#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

int main()
{
	int n = 0;
	cin >> n;

	queue<int> mainStreet;
	stack<int> secondaryStreet;

	for (int i = 0; i < n; i++)
	{
		int current = 0;
		cin >> current;

		mainStreet.push(current);
	}

	int carNumber = 1;

	while (true)
	{
		if (mainStreet.empty() && secondaryStreet.empty())
		{
			cout << "yes";

			return 0;
		}

		if (!mainStreet.empty() && secondaryStreet.empty())
		{
			if (mainStreet.front() == carNumber)
			{
				carNumber++;
			}
			else
			{
				secondaryStreet.push(mainStreet.front());
			}
				
			mainStreet.pop();
		}
		else if (mainStreet.empty() && !secondaryStreet.empty())
		{
			if (secondaryStreet.top() == carNumber)
			{
				secondaryStreet.pop();
				carNumber++;
			}
			else
			{
				cout << "no";

				return 0;
			}
		}
		else if (!mainStreet.empty() && !secondaryStreet.empty())
		{
			int mainLast = mainStreet.front();
			int secondaryLast = secondaryStreet.top();

			if (mainLast == carNumber)
			{
				mainStreet.pop();
				carNumber++;
			}
			else if (secondaryLast == carNumber)
			{
				secondaryStreet.pop();
				carNumber++;
			}
			else
			{
				secondaryStreet.push(mainLast);
				mainStreet.pop();
			}
		}
	}

	cout << "yes";

	while (true) {}
	return 0;
}