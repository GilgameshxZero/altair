#define _CRT_SECURE_NO_WARNINGS

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

typedef long long ll;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.in", "r", stdin);
	freopen ("output.out", "w", stdout);
#endif

	const ll INF = 1000000000000000; //1e15

	int t;
	cin >> t;

	for (int a = 0;a < t;a++) {
		int n, m, k;
		cin >> n >> m >> k;

		vector<vector<ll>> edge (n, vector<ll>(n, INF)), dist (n, vector<ll> (n, INF));
		for (int b = 0;b < m;b++) {
			int x, y;
			ll z;
			cin >> x >> y >> z;
			dist[x - 1][y - 1] = edge[x - 1][y - 1] = min (edge[x - 1][y - 1], z);
			dist[y - 1][x - 1] = edge[y - 1][x - 1] = min (edge[y - 1][x - 1], z);
		}

		vector<pair<int, int>> fam (k);
		for (int b = 0;b < k;b++) {
			cin >> fam[b].first >> fam[b].second;
			fam[b].first--;
			fam[b].second--;
		}

		for (int b = 0;b < n;b++)
			dist[b][b] = 0;
		for (int b = 0;b < n;b++)
			for (int c = 0;c < n;c++)
				for (int d = 0;d < n;d++)
					dist[c][d] = min (INF, min (dist[c][d], dist[c][b] + dist[b][d]));

		vector<pair<ll, ll>> ans (k); //(pickup new then dropoff, dropoff then pickup new)
		ans[0] = make_pair (dist[0][fam[0].first], dist[0][fam[0].first]);
		if (k > 1)
			ans[1] = make_pair (
				min (ans[0].first +
					dist[fam[0].first][fam[1].first] +
					dist[fam[1].first][fam[0].second],
					ans[0].second +
					dist[fam[0].first][fam[1].first] +
					dist[fam[1].first][fam[0].second]),
				min (ans[0].first +
					dist[fam[0].first][fam[0].second] +
					dist[fam[0].second][fam[1].first],
					ans[0].second +
					dist[fam[0].first][fam[0].second] +
					dist[fam[0].second][fam[1].first]));
		for (int b = 2;b < k;b++) {
			ans[b] = make_pair (
				min (ans[b - 1].first + 
					dist[fam[b - 2].second][fam[b].first] + 
					dist[fam[b].first][fam[b - 1].second], 
					ans[b - 1].second + 
					dist[fam[b - 1].first][fam[b].first] +
					dist[fam[b].first][fam[b - 1].second]),
				min (ans[b - 1].first + 
					dist[fam[b - 2].second][fam[b - 1].second] +
					dist[fam[b - 1].second][fam[b].first],					
					ans[b - 1].second + 
					dist[fam[b - 1].first][fam[b - 1].second] +
					dist[fam[b - 1].second][fam[b].first]));
			ans[b] = make_pair (min (ans[b].first, INF), min (ans[b].second, INF));
		}

		cout << "Case #" << a + 1 << ": ";
		ll fans;
		if (k >= 2)
			fans = min (ans[k - 1].first + dist[fam[k - 2].second][fam[k - 1].second], 
				ans[k - 1].second + dist[fam[k - 1].first][fam[k - 1].second]);
		else //k = 1
			fans = dist[0][fam[0].first] + dist[fam[0].first][fam[0].second];
		if (fans >= INF)
			fans = -1;
		cout << fans << '\n';
	}

	return 0;
}