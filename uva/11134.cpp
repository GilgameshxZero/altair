#include <algorithm>
#include <bitset>
#include <cassert>
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
#include <limits>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n, ans[2][5000], sel[2];
	pair< pair<int, int>, int > p3[2][5000]; //intervals are reversed
	bool f1;
	cin >> n;
	while (n != 0)
	{
		for (int a = 0;a < n;a++)
			cin >> p3[0][a].first.second >> p3[1][a].first.second >> p3[0][a].first.first >> p3[1][a].first.first,
			p3[0][a].second = p3[1][a].second = a;
		sort (p3[0], p3[0] + n); //sorted by b
		sort (p3[1], p3[1] + n);
		f1 = false;
		memset (ans[0], 0, sizeof (int) * n);
		memset (ans[1], 0, sizeof (int) * n);
		for (int a = 0, b;a < n;a++) //for 1 set of intervals
		{
			for (b = 0;b < n;b++) //pick 'smallest' unpicked interval that covers 'a'
				if (ans[0][p3[0][b].second] == 0 && a + 1 >= p3[0][b].first.second)
					break;
			if (b == n || a + 1 > p3[0][b].first.first)
				f1 = true;
			ans[0][p3[0][b].second] = a + 1;
		}
		for (int a = 0, b;a < n;a++)
		{
			for (b = 0;b < n;b++) //pick 'smallest' unpicked interval that covers 'a'
				if (ans[1][p3[1][b].second] == 0 && a + 1 >= p3[1][b].first.second)
					break;
			if (b == n || a + 1 > p3[1][b].first.first)
				f1 = true;
			ans[1][p3[1][b].second] = a + 1;
		}
		if (f1)
			cout << "IMPOSSIBLE\n";
		else
			for (int a = 0;a < n;a++)
				cout << ans[0][a] << " " << ans[1][a] << " " << "\n";
		cin >> n;
	}

	return 0;
}