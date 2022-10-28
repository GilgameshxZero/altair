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

bool comp (pair<int, int> &x, pair<int, int> &y)
{
	if (x.second == y.second)
		return x.first < y.first;
	return x.second < y.second;
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

	vector< pair<int, int> > wm (n);
	for (int a = 0;a < n;a++)
		cin >> wm[a].first >> wm[a].second;

	sort (wm.begin (), wm.end ());
	ll ans = 0, cur = 1;
	for (int a = 1;a < n;a++)
	{
		if (wm[a].first != wm[a - 1].first)
		{
			ans += cur * (cur - 1) / 2;
			cur = 0;
		}
		cur++;
	}
	ans += cur * (cur - 1) / 2;
	cur = 1;

	sort (wm.begin (), wm.end (), comp);
	for (int a = 1; a < n; a++)
	{
		if (wm[a].second != wm[a - 1].second)
		{
			ans += cur * (cur - 1) / 2;
			cur = 0;
		}
		cur++;
	}
	ans += cur * (cur - 1) / 2;
	cur = 1;

	for (int a = 1;a < n;a++)
	{
		if (wm[a] != wm[a - 1])
		{
			ans -= cur * (cur - 1) / 2;
			cur = 0;
		}
		cur++;
	}
	ans -= cur * (cur - 1) / 2;

	cout << ans;

	return 0;
}