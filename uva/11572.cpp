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

	int t;
	cin >> t;
	for (;t > 0;t--)
	{
		int n;
		cin >> n;
		vector<int> x;
		x.resize (n);

		for (int a = 0;a < n;a++)
			cin >> x[a];

		set<int> s;
		int l = 0, r = 0, ans = 1;
		s.insert (x[0]);
		while (r < n - 1)
		{
			if (s.insert (x[++r]).second == false)
			{
				while (x[l] != x[r])
					s.erase (x[l++]);
				l++;
				ans = max (r - l + 1, ans);
			}
			else
				ans = max (r - l + 1, ans);
		}
		cout << ans << "\n";
	}

	return 0;
}