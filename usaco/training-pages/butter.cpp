/*
ID: yangchess1
PROG: butter
LANG: C++
*/
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
#include <functional>
#include <fstream>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main ()
{
	ios_base::sync_with_stdio (false);
	std::freopen ("butter.in", "r", stdin);
	std::freopen ("butter.out", "w", stdout);

	int N, P, C;
	cin >> N >> P >> C;

	int past[500];
	for (int a = 0;a < N;a++)
	{
		cin >> past[a];
		past[a]--;
	}

	vector< pair<int, int> > edge[800];
	const int INF = 1e9;
	for (int a = 0, b, c, d;a < C;a++)
	{
		cin >> b >> c >> d;
		edge[b - 1].push_back (make_pair (c - 1, d));
		edge[c - 1].push_back (make_pair (b - 1, d));
	}

	vector<int> dist[500]; //distance from each cow to each pasture
	for (int a = 0;a < N;a++)
		dist[a].resize (P);

	//run dijkstra's on every cow with heap/priority queue
	priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > pq; //min-heaps (dist, past)
	bool vis[800];
	for (int a = 0;a < N;a++)
	{
		for (int b = 0;b < P;b++)
			dist[a][b] = INF;
		dist[a][past[a]] = 0;
		memset (vis, 0, sizeof (vis));
		pq.push (make_pair (0, past[a]));
		while (!pq.empty ())
		{
			int curr = pq.top ().second;
			pq.pop ();

			//no deletion
			if (vis[curr])
				continue;

			vis[curr] = true;

			//update from edges of curr
			for (int c = 0;c < edge[curr].size ();c++)
			{
				if (!vis[edge[curr][c].first] && dist[a][edge[curr][c].first] > dist[a][curr] + edge[curr][c].second)
				{
					dist[a][edge[curr][c].first] = dist[a][curr] + edge[curr][c].second;
					pq.push (make_pair (dist[a][edge[curr][c].first], edge[curr][c].first));
				}
			}
		}
	}

	//for every pasture sum up distance of cows to that pasture and take the smallest of these sums;
	int ans = INF;
	for (int a = 0;a < P;a++)
	{
		int sum = 0;
		for (int b = 0;b < N;b++)
			sum += dist[b][a];
		ans = min (ans, sum);
	}

	cout << ans << "\n";

	return 0;
}