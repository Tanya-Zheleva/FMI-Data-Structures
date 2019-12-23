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

	int q = 0;
	cin >> q;

	for (int i = 0; i < q; i++)
	{
		int p = 0;
		int x = 0;
		int y = 0;
		cin >> p >> x >> y;

		if (p == 1)
		{
			bool canReach = Find(x) == Find(y);
			cout << canReach;
		}
		else
		{
			Union(x, y);
		}
	}

	cout << endl;

	while (true) {}
	return 0;
}