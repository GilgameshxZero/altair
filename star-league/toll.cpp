//Solution by Yang Yan
//modified Floyd
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main ()
{
	freopen ("toll.in", "r", stdin);
	freopen ("toll.out", "w", stdout);

	int n, m, k;
	cin >> n >> m >> k;

	vector<int> cost (n);
	for (int a = 0;a < n;a++)
		cin >> cost[a];

	vector< vector<int> > best_dist (n, vector<int> (n, (int)1e8)), dist = best_dist;
	vector< pair<int, int> > sorted (n);
	for (int a = 0;a < n;a++)
		sorted[a] = make_pair (cost[a], a);
	sort (sorted.begin (), sorted.end ());

	for (int a = 0, b, c, d;a < m;a++)
	{
		cin >> b >> c >> d;
		dist[b - 1][c - 1] = dist[c - 1][b - 1] = min (dist[c - 1][b - 1], d);
		best_dist[b - 1][c - 1] = best_dist[c - 1][b - 1] = min (best_dist[b - 1][c - 1], dist[b - 1][c - 1] + max (cost[b - 1], cost[c - 1]));
	}

	for (int a = 0;a < n;a++)
		dist[a][a] = 0,
		best_dist[a][a] = cost[a];

	int ii;
	for (int a = 0;a < n;a++)
		for (int b = 0;b < n;b++)
			for (int c = 0;c < n;c++)
			{
				ii = dist[b][sorted[a].second] + dist[sorted[a].second][c];
				//if (cost[b] <= cost[sorted[a].second] && cost[c] <= cost[sorted[a].second])
					if (dist[b][c] > ii)
						dist[b][c] = dist[c][b] = ii,
						best_dist[b][c] = best_dist[c][b] = min (best_dist[b][c], dist[b][c] + max (cost[b], max (cost[c], sorted[a].first)));
						//cout << "dist from " << b + 1 << " to " << c + 1 << " through " << sorted[a].second + 1 << " updated to " << best_dist[b][c] << "\n";
			}

	for (int a = 0, b, c;a < k;a++)
		cin >> b >> c,
		cout << best_dist[b - 1][c - 1] << "\n";

	return 0;
}