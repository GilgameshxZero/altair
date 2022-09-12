//solution by Yang Yan
//DFS
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;

ll FindAnswer (vector< vector<ll> >& ch, vector<ll>& req, vector<ll>& cost, vector<ll>& mincost, ll x) //mincost is mincost of subtree at index i
{
	mincost[x] = cost[x];

	ll time = 0, tot = 0;
	for (int a = 0;a < ch[x].size ();a++)
	{
		time += FindAnswer (ch, req, cost, mincost, ch[x][a]);
		tot += req[ch[x][a]];
		mincost[x] = min (mincost[x], mincost[ch[x][a]]);
	}

	time += (max (0LL, req[x] - tot)) * mincost[x];
	req[x] = tot + max (req[x] - tot, 0LL);
	return time;
}

int main ()
{
	freopen ("tdec.in", "r", stdin);
	freopen ("tdec.out", "w", stdout);

	int n;
	cin >> n;

	vector< vector<ll> > ch (n);
	vector<ll> req (n), cost (n), mincost (n);
	int t;
	cin >> t >> req[0] >> cost[0];
	for (int a = 1, b;a < n;a++)
	{
		cin >> b >> req[a] >> cost[a];
		ch[b - 1].push_back (a);
	}

	cout << FindAnswer (ch, req, cost, mincost, 0) << "\n";

	return 0;
}