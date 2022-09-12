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

const int INF = 200000000;
long long ans;
vector<int> order;
int n, m, k, w, mat[1001][1001], dist[1001], src[1001];
char lvl[1001][10][10];
bool type[1001][1001], in_tree[1001];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n >> m >> k >> w;
	for (int a = 1;a <= k;a++)
	{
		for (int b = 0;b < n;b++)
		{
			cin.get ();
			for (int c = 0;c < m;c++)
				lvl[a][b][c] = cin.get ();
		}
	}

	for (int a = 1;a <= k;a++)
		for (int b = 1;b <= k;b++)
			mat[a][b] = INF;

	for (int a = 1;a <= k;a++)
	{
		for (int b = a + 1;b <= k;b++)
		{
			int diff = 0;

			for (int c = 0;c < n;c++)
				for (int d = 0;d < m;d++)
					if (lvl[b][c][d] != lvl[a][c][d])
						diff++;

			if (diff * w < n * m)
			{
				type[a][b] = type[b][a] = 1;
				mat[a][b] = mat[b][a] = diff * w;
			}
			else
			{
				type[a][b] = type[b][a] = 0;
				mat[a][b] = mat[b][a] = n * m;
			}
		}
	}

	//Prim's.
	for (int a = 1;a <= k;a++)
	{
		dist[a] = INF;
		in_tree[a] = false;
		src[a] = INF;
	}

	for (int a = 2;a <= k;a++)
	{
		dist[a] = mat[1][a];
		src[a] = 1;
	}

	in_tree[1] = true;
	order.push_back (1);
	ans = n * m;

	for (int a = 1;a < k;a++)
	{
		int small_dist = INF, small_id = INF;

		for (int b = 2;b <= k;b++)
		{
			if (in_tree[b] == false && dist[b] < small_dist)
			{
				small_id = b;
				small_dist = dist[b];
			}
		}

		in_tree[small_id] = true;
		order.push_back (small_id);
		ans += small_dist;

		//Update the distances and sources if needed
		for (int b = 2;b <= k;b++)
		{
			if (in_tree[b] == false && mat[small_id][b] < dist[b])
			{
				dist[b] = mat[small_id][b];
				src[b] = small_id;
			}
		}
	}

	cout << ans << "\n";
	for (int a = 0;a < order.size ();a++)
	{
		cout << order[a] << " ";
		if (src[order[a]] == INF || type[order[a]][src[order[a]]] == 0)
			cout << "0\n";
		else
			cout << src[order[a]] << "\n";
	}

	return 0;
}