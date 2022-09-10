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

void InitSegTree (vector<int> &cnt, vector< pair<int, int> > &range, string &total, int cur)
{
	if (range[cur].first == range[cur].second - 1)
	{
		if (range[cur].first < total.size () && total[range[cur].first] == '1')
			cnt[cur] = 1;
		else
			cnt[cur] = 0;
		return;
	}

	range[cur * 2].first = range[cur].first;
	range[cur * 2].second = (range[cur].first + range[cur].second) / 2;
	range[cur * 2 + 1].first = range[cur * 2].second;
	range[cur * 2 + 1].second = range[cur].second;

	InitSegTree (cnt, range, total, cur * 2);
	InitSegTree (cnt, range, total, cur * 2 + 1);

	cnt[cur] = cnt[cur * 2] + cnt[cur * 2 + 1];
}

void PropagateTo (vector<int> &cnt, vector< pair<int, int> > &range, vector<int> &lazy, int cur, int to)
{
	if (lazy[cur] == 0)
	{
		cnt[cur] = 0;
		if (cur * 2 < lazy.size ())
			lazy[cur * 2] = 0, lazy[cur * 2 + 1] = 0;
	}
	else if (lazy[cur] == 1)
	{
		cnt[cur] = range[cur].second - range[cur].first;
		if (cur * 2 < lazy.size ())
			lazy[cur * 2] = 1, lazy[cur * 2 + 1] = 1;
	}
	else if (lazy[cur] == 2)
	{
		cnt[cur] = range[cur].second - range[cur].first - cnt[cur];
		if (cur * 2 < lazy.size ())
		{
			if (lazy[cur * 2] == 0)
				lazy[cur * 2] = 1;
			else if (lazy[cur * 2] == 1)
				lazy[cur * 2] = 0;
			else if (lazy[cur * 2] == 2)
				lazy[cur * 2] = 3;
			else lazy[cur * 2] = 2;

			if (lazy[cur * 2 + 1] == 0)
				lazy[cur * 2 + 1] = 1;
			else if (lazy[cur * 2 + 1] == 1)
				lazy[cur * 2 + 1] = 0;
			else if (lazy[cur * 2 + 1] == 2)
				lazy[cur * 2 + 1] = 3;
			else lazy[cur * 2 + 1] = 2;
		}
	}

	lazy[cur] = 3;

	if (cur * 2 < lazy.size () && cur != to)
	{
		if (range[to].second <= range[cur * 2].second)
			PropagateTo (cnt, range, lazy, cur * 2, to);
		else
			PropagateTo (cnt, range, lazy, cur * 2 + 1, to);
	}
}

void Update (vector<int> &cnt, vector< pair<int, int> > &range, vector<int> &lazy, int type, int cur, int x, int y)
{
	if (range[cur].first >= x && range[cur].second <= y)
	{
		if (type != 2)
			lazy[cur] = type;
		else if (lazy[cur] == 0)
			lazy[cur] = 1;
		else if (lazy[cur] == 1)
			lazy[cur] = 0;
		else if (lazy[cur] == 2)
			lazy[cur] = 3;
		else
			lazy[cur] = 2;
	}
	else if (range[cur].second <= x || range[cur].first >= y)
		return;
	else
	{
		PropagateTo (cnt, range, lazy, cur, cur);
		Update (cnt, range, lazy, type, cur * 2, x, y);
		Update (cnt, range, lazy, type, cur * 2 + 1, x, y);
		PropagateTo (cnt, range, lazy, cur * 2, cur * 2);
		PropagateTo (cnt, range, lazy, cur * 2 + 1, cur * 2 + 1);
		cnt[cur] = cnt[cur * 2] + cnt[cur * 2 + 1];
	}
}

int GetCount (vector<int> &cnt, vector< pair<int, int> > &range, vector<int> &lazy, int cur, int x, int y)
{
	PropagateTo (cnt, range, lazy, cur, cur);
	if (range[cur].first >= x && range[cur].second <= y)
		return cnt[cur];
	else if (range[cur].second <= x || range[cur].first >= y)
		return 0;
	else
		return GetCount (cnt, range, lazy, cur * 2, x, y) + GetCount (cnt, range, lazy, cur * 2 + 1, x, y);
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.in", "r", stdin);
	freopen ("output.out", "w", stdout);
#endif

	int t;
	cin >> t;

	for (int a = 0;a < t;a++)
	{
		cout << "Case " << a + 1 << ":\n";

		int m;
		cin >> m;

		string total;
		for (int b = 0;b < m;b++)
		{
			int k;
			cin >> k;
			string s;
			cin >> s;

			for (int c = 0;c < k;c++)
				total.append (s);
		}

		int ub = 1;
		while (ub < total.length ())
			ub *= 2;
		vector<int> cnt (ub * 2, 0), lazy (ub * 2, 3);
		vector< pair<int, int> > range (ub * 2);
		range[1] = make_pair (0, ub);
		InitSegTree (cnt, range, total, 1);

		int q, qc = 1;
		cin >> q;

		for (int b = 0;b < q;b++)
		{
			char type;
			cin >> type;
			int x, y;
			cin >> x >> y;
			y++;

			if (type == 'F')
				Update (cnt, range, lazy, 1, 1, x, y);
			else if (type == 'E')
				Update (cnt, range, lazy, 0, 1, x, y);
			else if (type == 'I')
				Update (cnt, range, lazy, 2, 1, x, y);
			else
				cout << "Q" << qc++ << ": " << GetCount (cnt, range, lazy, 1, x, y) << "\n";
		}
	}

	return 0;
}