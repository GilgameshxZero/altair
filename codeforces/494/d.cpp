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

const int MOD = 1e9+7;

void Prep1 (vector<int>& ssize, vector<int>& v, vector<int>& k, vector< vector< pair<int, int> > >& edge, int x, int par)
{
	ssize[x] = 1;
	v[x] = k[x] = 0;

	for (int a = 0;a < edge[x].size ();a++)
	{
		if (edge[x][a].first == par)
			continue;
		Prep1 (ssize, v, k, edge, edge[x][a].first, x);
		ssize[x] += ssize[edge[x][a].first];
		v[x] += ((ll)v[edge[x][a].first] + (ll)ssize[edge[x][a].first] * edge[x][a].second) % MOD;
		k[x] += ((ll)k[edge[x][a].first] + (ll)edge[x][a].second * edge[x][a].second + 2LL * edge[x][a].second * v[edge[x][a].first]) % MOD;
	}
}

void Prep2 (vector<int>& ssize, vector<int>& v, vector<int>& k, vector<int>& w, vector<int>& q, vector< vector< pair<int, int> > >& edge, int x, int par, int len)
{
	if (par = -1)
	{
		w[x] = 0;
		q[x] = 0;
	}
	else
	{
		w[x] = ((ll)w[par] + (ll)(ssize[0] - ssize[par] + 1) * len + (ll)v[par] - 
			(ll)v[x] - (ll)ssize[x] * len + (ll)(ssize[par] - ssize[x] - 1) * len) % MOD;
		//q[x] = q[par] + (ll)(ssize[0] - ssize[par] + 1) * ((ll)len * len % MOD) + 2LL * w[par] * len
		//	+ k[par] - k[x] - len * len % MOD * ssize[x]
	}

	for (int a = 0;a < edge[x].size ();a++)
	{
		if (edge[x][a].first == par)
			continue;
		Prep2 (ssize, v, k, w, q, edge, edge[x][a].first, x, edge[x][a].second);
	}
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n;
	cin >> n;

	vector< vector< pair< int, int > > > edge (n);
	for (int a = 0, b, c, d;a < n - 1;a++)
	{
		cin >> b >> c >> d;
		edge[b - 1].push_back (make_pair (c - 1, d));
		edge[c - 1].push_back (make_pair (b - 1, d));
	}

	//traverse for stuff
	vector<int> ssize (n), //subtree size
		v (n), //sum of dist to subtree
		k (n), //sum of dist to subtree^2
		w (n), //sum of dist to anything outside that comes from parent
		q (n); //w dists^2
	Prep1 (ssize, v, k, edge, 0, -1);
	Prep2 (ssize, v, k, w, q, edge, 0, -1, -1);

	return 0;
}