//Solution by Yang Yan
//2nd solution
//Bellman-Ford

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main ()
{
	freopen ("jobhunt.in", "r", stdin);
	freopen ("jobhunt.out", "w", stdout);

	int D, P, C, F, S;
	cin >> D >> P >> C >> F >> S;

	vector< pair< pair<int, int>, int > > edge;
	for (int a = 0, b, c;a < P;a++)
	{
		cin >> b >> c;
		edge.push_back (make_pair (make_pair (b - 1, c - 1), -D));
	}
	for (int a = 0, b, c, d;a < F;a++)
	{
		cin >> b >> c >> d;
		edge.push_back (make_pair (make_pair (b - 1, c - 1), d - D));
	}

	//bellman-ford
	vector<int> dist (C, 1e9);
	dist[S - 1] = 0;
	int last_change = 0;
	for (int a = 0;a < C;a++)
	{
		for (int b = 0;b < edge.size ();b++)
			if (dist[edge[b].first.second] > dist[edge[b].first.first] + edge[b].second)
				dist[edge[b].first.second] = dist[edge[b].first.first] + edge[b].second,
				last_change = a;
		if (last_change < a)
			break;
	}

	if (last_change == C - 1)
		cout << "-1\n";

	//find ans
	int ans = 0;
	for (int a = 0;a < C;a++)
		ans = min (ans, dist[a]);

	cout << -ans + D << "\n";

	return 0;
}