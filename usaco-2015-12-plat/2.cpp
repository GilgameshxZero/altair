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

//segtree

int n;
vector<bool> el;
vector<int> ord, bes;
vector< pair<int, pair<int, int> > > segtree[2]; //(match, leftover neg, leftover pos)

void FenAdd (vector<int>& fen, int k, int x)
{
	for (; x < fen.size (); x += (x & -x))
		fen[x] += k;
}

int FenSum (vector<int>& fen, int x)
{
	int r = 0;
	for (; x > 0; x -= (x & -x))
		r += fen[x];
	return r;
}

void UpdateNode1 (vector< pair<int, pair<int, int> > > &tree, int ind, int k, bool first)
{
	ind += 65536 * 2 - 1; //-1
	if (first)
		tree[ind].second.first += k;
	else
		tree[ind].second.second += k;
	ind /= 2;

	while (ind != 0)
	{
		int a = min (tree[ind * 2].second.first, tree[ind * 2 + 1].second.second);
		tree[ind].first = tree[ind * 2].first + tree[ind * 2 + 1].first + a;
		tree[ind].second.first = tree[ind * 2].second.first + tree[ind * 2 + 1].second.first - a;
		tree[ind].second.second = tree[ind * 2].second.second + tree[ind * 2 + 1].second.second - a;
		ind /= 2;
	}
}

void UpdateNode2 (vector< pair<int, pair<int, int> > > &tree, int ind, int k, bool first)
{
	ind += 65536 * 2 - 1; //-1
	if (first)
		tree[ind].second.first += k;
	else
		tree[ind].second.second += k;
	ind /= 2;

	while (ind != 0)
	{
		int a = min (tree[ind * 2].second.second, tree[ind * 2 + 1].second.first);
		tree[ind].first = tree[ind * 2].first + tree[ind * 2 + 1].first + a;
		tree[ind].second.first = tree[ind * 2].second.first + tree[ind * 2 + 1].second.first - a;
		tree[ind].second.second = tree[ind * 2].second.second + tree[ind * 2 + 1].second.second - a;
		ind /= 2;
	}
}

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("cardgame.in", "r", stdin);
	std::freopen ("cardgame.out", "w", stdout);

	cin >> n;
	el.resize (2 * n + 1, false);

	for (int a = 0, b; a < n; a++)
	{
		cin >> b;
		ord.push_back (b);
		el[b] = true;
	}

	for (int a = 1; a <= 2 * n; a++)
	{
		if (el[a] == false)
			bes.push_back (a);
	}

	segtree[0].resize (131072 * 2); //2^17
	segtree[1].resize (131072 * 2); //2^17

	for (int a = 0; a < n; a++)
	{
		UpdateNode2 (segtree[1], ord[a], 1, true);
		UpdateNode2 (segtree[1], bes[a], 1, false);
	}

	int ans = 0;
	ans = max (ans, segtree[1][1].first);

	for (int a = 0; a < n; a++)
	{
		UpdateNode2 (segtree[1], ord[a], -1, true);
		UpdateNode2 (segtree[1], bes[n - a - 1], -1, false);
		UpdateNode1 (segtree[0], ord[a], 1, true);
		UpdateNode1 (segtree[0], bes[n - a - 1], 1, false);
		ans = max (ans, segtree[0][1].first + segtree[1][1].first);
	}

	cout << ans << '\n';

	return 0;
}