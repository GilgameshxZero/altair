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
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

//adds k to the element at pos x
void FenAdd (vector<int>& fen, int x, int k)
{
	for (;x < fen.size ();x += (x & -x))
		fen[x] += k;
}

//sums all elements before and including x
int FenSum (vector<int>& fen, int x)
{
	int r = 0;
	for (;x > 0;x -= (x & -x))
		r += fen[x];
	return r;
}

int Dist (pair<int, int>& x, pair<int, int>& y)
{
	return abs (x.first - y.first) + abs (x.second - y.second);
}

void InitSegtree (vector<int>& seg, vector< pair<int, int> >& range, int x)
{
	if (x >= seg.size () / 2)
	{
		range[x].first = x - seg.size () / 2;
		range[x].second = range[x].first;
		return;
	}

	InitSegtree (seg, range, x * 2);
	InitSegtree (seg, range, x * 2 + 1);

	seg[x] = max (seg[x * 2], seg[x * 2 + 1]);
	range[x].first = range[x * 2].first;
	range[x].second = range[x * 2 + 1].second;
}

int GetMax (vector<int>& seg, vector< pair<int, int> >& range, int x, int y, int cur) //get max b/t x and y inc at current node
{
	if (range[cur].first > y || range[cur].second < x)
		return 0;
	if (range[cur].first == range[cur].second)
		return seg[cur];
	if (range[cur].first >= x && range[cur].second <= y)
		return seg[cur];

	return max (GetMax (seg, range, x, y, cur * 2), GetMax (seg, range, x, y, cur * 2 + 1));
}

void UpdateSegtree (vector<int>& seg, int x, int k) //update node x with k and propagate up
{
	seg[x] = k;
	x /= 2;
	while (x != 0)
	{
		seg[x] = max (seg[x * 2], seg[x * 2 + 1]);
		x /= 2;
	}
}

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("marathon.in", "r", stdin);
	std::freopen ("marathon.out", "w", stdout);

	int n, q;
	cin >> n >> q;

	vector< pair<int, int> > loc (n);
	for (int a = 0;a < n;a++)
		cin >> loc[a].first >> loc[a].second;

	//build fenwick tree
	vector<int> fen (n, 0); //pos i contains dist from i-1 to i
	for (int a = 0;a < n - 1;a++)
		FenAdd (fen, a + 1, Dist (loc[a], loc[a + 1]));

	//build max-segtree of dist subtractions
	//get power of two >= n
	int dig = 0;
	for (;(n >> dig) > 0;dig++);
	dig++; //nodes in segtree

	int beg = (1 << (dig - 1));
	
	vector<int> seg ((1 << dig), 0); //seg[0] is unused
	vector< pair<int, int> > range ((1 << dig));
	//init values in segtree
	for (int a = 1;a < n - 1;a++)
		seg[beg + a] = Dist (loc[a - 1], loc[a]) + Dist (loc[a], loc[a + 1]) - Dist(loc[a - 1], loc[a + 1]);

	InitSegtree (seg, range, 1);

	//process queries
	pair<int, int> tp;
	for (int a = 0, b, c, d;a < q;a++)
	{
		char x;
		cin >> x;

		if (x == 'Q')
		{
			cin >> b >> c;
			if (b + 1 >= c)
				cout << FenSum (fen, c - 1) - FenSum (fen, b - 1) << "\n";
			else
				cout << FenSum (fen, c - 1) - FenSum (fen, b - 1) - GetMax (seg, range, b, c - 2, 1) << "\n";
		}
		else
		{
			cin >> b >> c >> d;
			b--;
			tp = make_pair (c, d);

			if (b != 0)
				FenAdd (fen, b, -Dist (loc[b - 1], loc[b]) + Dist (loc[b - 1], tp));
			if (b != n - 1)
				FenAdd (fen, b + 1, -Dist (loc[b], loc[b + 1]) + Dist (tp, loc[b + 1]));

			if (b != 0 && b != n - 1)
			{
				UpdateSegtree (seg, beg + b, Dist (loc[b - 1], tp) + Dist (tp, loc[b + 1]) - Dist (loc[b - 1], loc[b + 1]));

				if (b != 1)
					UpdateSegtree (seg, beg + b - 1, Dist (loc[b - 2], loc[b - 1]) + Dist (loc[b - 1], tp) - Dist (loc[b - 2], tp));
				if (b != n - 2)
					UpdateSegtree (seg, beg + b + 1, Dist (tp, loc[b + 1]) + Dist (loc[b + 1], loc[b + 2]) - Dist (tp, loc[b + 2]));
			}
			loc[b] = tp;
		}
	}

	return 0;
}