#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int main()
{
	int n = 0;
	cin >> n;
	int position = 0;
	cin >> position;

	queue<int> jobs;
	queue<int> positions;
	priority_queue<int> sortedJobs;

	for (int i = 0; i < n; i++)
	{
		int current = 0;
		cin >> current;

		jobs.push(current);
		positions.push(i);
		sortedJobs.push(current);
	}

	int time = 0;

	while (true)
	{
		int firstJob = jobs.front();
		int currentPosition = positions.front();
		int highestPriorityJob = sortedJobs.top();

		if (currentPosition == position && highestPriorityJob <= firstJob)
		{
			time++;
			cout << time << endl;
			break;
		}

		if (highestPriorityJob > firstJob)
		{
			jobs.pop();
			positions.pop();
			jobs.push(firstJob);
			positions.push(currentPosition);
		}
		else
		{
			jobs.pop();
			positions.pop();
			sortedJobs.pop();
			time++;
		}
	}

	while (true) {}
	return 0;
}