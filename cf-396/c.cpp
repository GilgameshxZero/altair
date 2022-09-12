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

typedef long long ll;

using namespace std;

const int MOD = 1e9+7;
int n, ind, first[300001], last[300001], level[300001], 
	seg[2][1048576], lazy[2][1048576], 
	range[1048576][2]; //inc-inc
vector<int> ch[300001];

void DFS (int v, int lvl)
{
	level[v] = lvl;
	first[v] = ind++;
	for (int a = 0;a < ch[v].size ();a++)
		DFS (ch[v][a], lvl + 1);
	last[v] = ind - 1;
}

void InitRange (int v)
{
	if (v >= 524288)
		return;
	range[v * 2][0] = range[v][0];
	range[v * 2][1] = ((ll)range[v][0] + range[v][1]) / 2;
	range[v * 2 + 1][0] = range[v * 2][1] + 1;
	range[v * 2 + 1][1] = range[v][1];
	InitRange (v * 2);
	InitRange (v * 2 + 1);
}

void Propagate (int s, int v)
{
	seg[s][v] = ((ll)seg[s][v] + lazy[s][v]) % MOD;
	if (v < 524288)
		lazy[s][v * 2] = ((ll)lazy[s][v * 2] + lazy[s][v]) % MOD, 
		lazy[s][v * 2 + 1] = ((ll)lazy[s][v * 2 + 1] + lazy[s][v]) % MOD;
	lazy[s][v] = 0;
}

void Update (int s, int v, int f, int l, int k)
{
	if (range[v][0] >= f && range[v][1] <= l)
		lazy[s][v] = ((ll)lazy[s][v] + k) % MOD;
	else if (l < range[v][0] || f > range[v][1])
		return;
	else
	{
		//seg[s][v] = ((ll)seg[s][v] + k) % MOD;
		Propagate (s, v);
		Update (s, v * 2, f, l, k);
		Update (s, v * 2 + 1, f, l, k);
	}
}

int Get (int node, int v)
{
	Propagate (0, v);
	Propagate (1, v);
	if (range[v][0] == node && range[v][1] == node)
		return (int)(((ll)seg[0][v] + (ll)MOD * MOD - (ll)seg[1][v] * level[node]) % MOD);
	else if (node <= range[v * 2][1])
		return Get (node, v * 2);
	else
		return Get (node, v * 2 + 1);
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;
	for (int a = 2, b;a <= n;a++)
		cin >> b,
		ch[b].push_back (a);

	ind = 1;
	DFS (1, 1);

	range[1][0] = 1;
	range[1][1] = 524288;
	InitRange (1);

	memset (seg, 0, sizeof (seg));
	memset (lazy, 0, sizeof (lazy));

	int k;
	cin >> k;
	for (int a = 0, b, c, d;a < k;a++)
	{
		cin >> b;
		if (b == 1)
		{
			cin >> b >> c >> d;
			Update (0, 1, first[b], last[b], (int)(((ll)c + (ll)level[b] * d) % MOD));
			Update (1, 1, first[b], last[b], d);
		}
		else
		{
			cin >> b;
			cout << Get (b, 1) << "\n";
		}
	}

	return 0;
}