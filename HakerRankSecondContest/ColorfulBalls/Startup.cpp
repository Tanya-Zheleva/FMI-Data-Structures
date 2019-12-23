#include <iostream>

using namespace std;

int ranking[1024];
int parent[1024];

void MakeSet(int n)
{
	for (int i = 0; i < n; i++)
	{
		parent[i] = i;
	}
}

int Find(int x)
{
	if (parent[x] != x)
	{
		parent[x] = Find(parent[x]);
	}

	return parent[x];
}

void Union(int x, int y)
{
	int xSet = Find(x);
	int ySet = Find(y);

	if (xSet == ySet) return;

	if (ranking[xSet] < ranking[ySet])
	{
		parent[xSet] = ySet;
	}
	else if (ranking[xSet] > ranking[ySet])
	{
		parent[ySet] = xSet;
	}
	else
	{
		parent[ySet] = xSet;
		ranking[xSet] = ranking[xSet] + 1;
	}
}

int CountDistinct(int n)
{
	int res = 1;

	for (int i = 1; i < n; i++)
	{
		int j = 0;

		for (j = 0; j < i; j++)
		{
			if (parent[i] == parent[j])
			{
				break;
			}
		}

		if (i == j) res++;
	}

	return res;
}

int main()
{
	int n = 0;
	int m = 0;
	cin >> n >> m;
	MakeSet(n);

	for (int i = 0; i < m; i++)
	{
		int x = 0;
		int y = 0;
		cin >> x >> y;

		Union(x, y);
	}

	cout << CountDistinct(n);

	cout << endl;

	while (true) { }
	return 0;
}