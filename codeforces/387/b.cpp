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

	int n, m, x[3000], y[3000];
	cin >> n >> m;
	for (int a = 0;a < n;a++)
		cin >> x[a];
	for (int a = 0;a < m;a++)
		cin >> y[a];

	int ans = 0;
	for (int a = 0, b = 0;a < n;a++)
	{
		bool f1 = false;
		for (;b < m;b++)
		{
			if (x[a] <= y[b])
			{
				f1 = true;
				b++;
				break;
			}
		}

		if (!f1)
			ans++;
	}

	cout << ans << "\n";

	return 0;
}