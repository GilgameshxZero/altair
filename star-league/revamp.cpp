//Solution by yang Yan
//Dijkstra's on modified graph

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <functional>
#include <bitset>
using namespace std;

typedef long long ll;

int main ()
{
	freopen ("revamp.in", "r", stdin);
	freopen ("revamp.out", "w", stdout);

	int N, M, K;
	cin >> N >> M >> K;

	//K levels, each with N vertices and the M edges.
	vector< vector< pair<int, int> > > edge ((K + 1) * N);
	for (int a = 0, b, c, d;a < M;a++)
	{
		cin >> b >> c >> d;
		b--;
		c--;
		for (int e = 0;e <= K;e++)
			edge[e * N + b].push_back (make_pair (e * N + c, d)),
			edge[e * N + c].push_back (make_pair (e * N + b, d));
		for (int e = 0;e < K;e++)
			edge[e * N + b].push_back (make_pair ((e + 1) * N + c, 0)),
			edge[e * N + c].push_back (make_pair ((e + 1) * N + b, 0));
	}
	for (int a = 0;a < N;a++)
		for (int b = 0;b < K;b++)
			edge[b * N + a].push_back (make_pair ((b + 1) * N + a, 0));

	//run dijkstra's from (0, 0) to (N - 1, K)
	vector<int> dist (edge.size (), -1);
	priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > pq;
	pq.push (make_pair (0, 0));
	pair<int, int> pii;
	int end_vert = K * N + N - 1;
	while (!pq.empty ())
	{
		pii = pq.top ();
		pq.pop ();
		if (dist[pii.second] != -1)
			continue;
		dist[pii.second] = pii.first;
		if (pii.second == end_vert)
			break;

		//update distances
		for (int a = 0;a < edge[pii.second].size ();a++)
			if (dist[edge[pii.second][a].first] == -1)
				pq.push (make_pair (dist[pii.second] + edge[pii.second][a].second, edge[pii.second][a].first));
	}

	cout << dist[end_vert] << "\n";

	return 0;
}