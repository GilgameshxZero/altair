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

//segtree lazy
const int NODES = 524288, start_x = 262144;
int n, q;
vector<ll> mintree, ttree, lazy;
vector< pair<int, int> > range;

void PropagateLazy (int root)
{
	int left = root * 2, right = left + 1;

	if (root < start_x)
	{
		lazy[left] = lazy[left] + lazy[root];
		lazy[right] = lazy[right] + lazy[root];
	}
	ttree[root] += lazy[root] * (range[root].second - range[root].first + 1);
	mintree[root] += lazy[root];
	lazy[root] = 0;
}

void AddBale (int root, int x, int y, ll k) //inc
{
	int left = root * 2, right = left + 1;

	if (x <= range[root].first && y >= range[root].second) //spans entire range
	{
		lazy[root] += k;
		PropagateLazy (root);
	}
	else if (y <= range[left].second) //L ch only
	{
		PropagateLazy (root);
		AddBale (left, x, y, k);
		PropagateLazy (left);
		PropagateLazy (right);
		ttree[root] = ttree[left] + ttree[right];
		mintree[root] = min (mintree[left], mintree[right]);
	}
	else if (x >= range[right].first) //R ch only
	{
		PropagateLazy (root);
		AddBale (right, x, y, k);
		PropagateLazy (left);
		PropagateLazy (right);
		ttree[root] = ttree[left] + ttree[right];
		mintree[root] = min (mintree[left], mintree[right]);
	}
	else //spans across middle line
	{
		PropagateLazy (root);
		AddBale (left, x, y, k);
		AddBale (right, x, y, k);
		PropagateLazy (left);
		PropagateLazy (right);
		ttree[root] = ttree[left] + ttree[right];
		mintree[root] = min (mintree[left], mintree[right]);
	}
}

ll GetMin (int root, int x, int y)
{
	int left = root * 2, right = left + 1;

	if (x <= range[root].first && y >= range[root].second) //spans entire range
	{
		PropagateLazy (root);
		return mintree[root];
	}
	else if (y <= range[left].second) //L ch only
	{
		PropagateLazy (root);
		return GetMin (left, x, y);
	}
	else if (x >= range[right].first) //R ch only
	{
		PropagateLazy (root);
		return GetMin (right, x, y);
	}
	else //spans across middle line
	{
		PropagateLazy (root);
		return min (GetMin (left, x, y), GetMin (right, x, y));
	}
}

ll GetTotal (int root, int x, int y)
{
	int left = root * 2, right = left + 1;

	if (x <= range[root].first && y >= range[root].second) //spans entire range
	{
		PropagateLazy (root);
		return ttree[root];
	}
	else if (y <= range[left].second) //L ch only
	{
		PropagateLazy (root);
		return GetTotal (left, x, y);
	}
	else if (x >= range[right].first) //R ch only
	{
		PropagateLazy (root);
		return GetTotal (right, x, y);
	}
	else //spans across middle line
	{
		PropagateLazy (root);
		return GetTotal (left, x, y) + GetTotal (right, x, y);
	}
}

void InitSTree (int root)
{
	if (root >= start_x)
		return;

	int mid = (range[root].first + range[root].second) / 2;
	range[root * 2] = make_pair (range[root].first, mid);
	range[root * 2 + 1] = make_pair (mid + 1, range[root].second);

	InitSTree (root * 2);
	InitSTree (root * 2 + 1);
}

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("haybales.in", "r", stdin);
	std::freopen ("haybales.out", "w", stdout);

	cin >> n >> q;

	mintree.resize (NODES + 1);
	ttree.resize (NODES + 1);
	lazy.resize (NODES + 1);
	range.resize (NODES + 1);
	range[1].first = 1;
	range[1].second = start_x;
	InitSTree (1);

	for (int a = 0, b; a < n; a++)
	{
		cin >> b;
		AddBale (1, a + 1, a + 1, b);
	}

	ll d;
	string s;
	for (int a = 0, b, c, x; a < q; a++)
	{
		cin >> s;

		if (s == "M")
		{
			cin >> b >> c;
			cout << GetMin (1, b, c) << '\n';
		}
		else if (s == "P")
		{
			cin >> b >> c >> d;
			AddBale (1, b, c, d);
		}
		else if (s == "S")
		{
			cin >> b >> c;
			cout << GetTotal (1, b, c) << '\n';
		}
	}

	return 0;
}