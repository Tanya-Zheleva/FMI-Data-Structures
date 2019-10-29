#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void Fill(vector<int>& items, int n)
{
	for (int i = 0; i < n; i++)
	{
		int current = 0;
		cin >> current;
		items[i] = current;
	}
}

int main()
{
	int g = 0;
	cin >> g;	

	for (int i = 0; i < g; i++)
	{
		int n = 0, m = 0, x = 0;
		cin >> n >> m >> x;

		vector<int> a(n);
		vector<int> b(m);

		Fill(a, n);
		Fill(b, m);

		int sum = 0, turns = 0, aTurns = 0, bTurns = 0;

		while (sum + a[aTurns] <= x && aTurns < n) //Add only if it won't be greater than x
		{
			sum += a[aTurns];
			aTurns++;
			turns++;
		}
		
		while (aTurns >= 0 && bTurns < m) 
		{
			sum += b[bTurns];
			bTurns++;

			while (sum > x && aTurns > 0) //Remove from a until a new item from b can be added
			{
				aTurns--;
				sum -= a[aTurns];
			}

			if (sum <= x && aTurns + bTurns > turns) 
			{
				turns = aTurns + bTurns;
			}
		}

		cout << turns << endl;
	}

	while (true) { }
	return 0;
}