#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int n, m, x[200001], type[200001], vis[2][200001], first[2][200001], last[2][200001], cnt[2], fen[2][200001], father[200001];
vector<int> edge[200001];

void DFS (int node, int par, int *num1, int *num2, int fa)
{
	if (par)
	{
		vis[par][*num2] = node;
		first[par][node] = (*num2)++;
	}
	else
	{
		vis[par][*num1] = node;
		first[par][node] = (*num1)++;
	}

	for (int a = 0;a < edge[node].size ();a++)
	{
		if (edge[node][a] == fa) continue;
		DFS (edge[node][a], par ^ 1, num1, num2, node);
	}

	father[node] = fa;
	type[node] = par;
	if (par)
		last[par][node] = *num2 - 1;
	else
		last[par][node] = *num1 - 1;
}

void Add (int par, int index, int val)
{
	for (int a = index;a < cnt[par];a += a & -a)
		fen[par][a] += val;
}

int Sum (int par, int index)
{
	int r = 0;
	for (int a = index;a > 0;a -= a & -a)
		r += fen[par][a];
	return r;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n >> m;
	for (int a = 1;a <= n;a++)
		cin >> x[a];
	for (int a = 0, b, c;a < n - 1;a++)
	{
		cin >> b >> c;
		edge[b].push_back (c);
		edge[c].push_back (b);
	}

	cnt[0] = cnt[1] = 1;
	DFS (1, 0, &cnt[0], &cnt[1], -1);

	for (int a = 0, b, c, d;a < m;a++)
	{
		cin >> b;
		if (b == 1)
		{
			cin >> c >> d;
			Add (type[c], first[type[c]][c], d);
			Add (type[c], last[type[c]][c] + 1, -d);

			for (int e = 0;e < edge[c].size ();e++)
			{
				if (edge[c][e] == father[c]) continue;
				Add (type[edge[c][e]], first[type[edge[c][e]]][edge[c][e]], -d);
				Add (type[edge[c][e]], last[type[edge[c][e]]][edge[c][e]] + 1, d);
			}
		}
		else
		{
			cin >> c;
			cout << x[c] + Sum (type[c], first[type[c]][c]) << "\n";
		}
	}

	return 0;
}