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

double totcomb;

double C3 (int x)
{
	return (double)x / 2 / 3 * (x - 1) * (x - 2);
}

void CalcSub (vector< vector< pair<int, int> > >& edge, vector<int>& ssize, int cur, int par)
{
	ssize[cur] = 1;

	for (int a = 0;a < edge[cur].size ();a++)
	{
		if (edge[cur][a].first == par)
			continue;
		CalcSub (edge, ssize, edge[cur][a].first, cur);
		ssize[cur] += ssize[edge[cur][a].first];
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

	vector< vector< pair<int, int> > > edge (n);
	vector< pair< pair<int, int>, int> > orig (n - 1);
	for (int a = 0, b, c, d;a < n - 1;a++)
	{
		cin >> b >> c >> d;
		orig[a] = make_pair (make_pair (b - 1, c - 1), d);
		edge[b - 1].push_back (make_pair (c - 1, d));
		edge[c - 1].push_back (make_pair (b - 1, d));
	}

	//calc subtree sizes
	vector<int> ssize (n);
	totcomb = C3 (n);
	CalcSub (edge, ssize, 0, -1);

	//calc exp
	double expect = 0;
	for (int a = 0;a < n - 1;a++)
	{
		if (ssize[orig[a].first.first] > ssize[orig[a].first.second])
			expect += 2 * orig[a].second / totcomb * (totcomb - C3 (ssize[orig[a].first.second]) - C3 (n - ssize[orig[a].first.second]));
		else
			expect += 2 * orig[a].second / totcomb * (totcomb - C3 (ssize[orig[a].first.first]) - C3 (n - ssize[orig[a].first.first]));
	}

	//query
	int q;
	cin >> q;
	cout << fixed << setprecision (12);
	for (int a = 0, b, c;a < q;a++)
	{
		cin >> b >> c;
		b--;
		if (ssize[orig[b].first.first] > ssize[orig[b].first.second])
			expect -= 2 * (orig[b].second - c) / totcomb * (totcomb - C3 (ssize[orig[b].first.second]) - C3 (n - ssize[orig[b].first.second]));
		else
			expect -= 2 * (orig[b].second - c) / totcomb * (totcomb - C3 (ssize[orig[b].first.first]) - C3 (n - ssize[orig[b].first.first]));
		cout << expect << "\n";
		orig[b].second = c;
	}

	return 0;
}