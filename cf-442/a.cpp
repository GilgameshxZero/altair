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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	vector<string> vec;
	string temp, colors = "RGBYW";
	int n, ans;

	cin >> n;
	for (int a = 0;a < n;a++)
	{
		cin >> temp;
		vec.push_back (temp);
	}

	ans = 10;
	for (int a = 0;a < (1 << 10);a++)
	{
		int cnt = 0;
		for (int b = 0;b < 10;b++)
			if ((a >> b) & 1)
				cnt++;

		if (cnt >= ans)
			continue;

		bool hint[128];
		memset (hint, 0, sizeof (hint));
		for (int b = 0;b < 5;b++)
			if ((a >> b) & 1)
				hint[colors[b]] = true;
		for (int b = 0;b < 5;b++)
			if ((a >> (b + 5)) & 1)
				hint['1' + b] = true;

		bool flag = false;
		for (int b = 0;b < n;b++)
		{
			for (int c = 0;c < n;c++)
			{
				if (vec[b] != vec[c])
				{
					if (vec[b][0] != vec[c][0] && (hint[vec[b][0]] || hint[vec[c][0]])) continue;
					if (vec[b][1] != vec[c][1] && (hint[vec[b][1]] || hint[vec[c][1]])) continue;
					flag = true;
				}
			}
		}

		if (!flag)
			ans = cnt;
	}

	cout << ans << "\n";

	return 0;
}