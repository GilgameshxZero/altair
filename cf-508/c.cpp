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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int M, T, R;
	cin >> M >> T >> R;

	int w[300];
	for (int a = 0;a < M;a++)
		cin >> w[a];

	int ans = R, rem[300];
	fill (rem, rem + 300, R);

	if (T < R)
	{
		cout << "-1\n";
		return 0;
	}

	for (int a = 0;a < R;a++)
		for (int b = 0;b < M;b++)
			if (w[b] <= w[0] - a + T - 1)
				rem[b]--;

	for (int a = 0;a < M;a++)
	{
		if (rem[a] <= 0)
			continue;
		if (w[a] - w[a - 1] < rem[a])
		{
			cout << "-1\n";
			return 0;
		}
		ans += rem[a];
		for (int b = 0, r = rem[a];b < r;b++)
			for (int c = 0;c < M;c++)
				if (w[c] <= w[a] - b + T - 1)
					rem[c]--;
	}

	cout << ans << "\n";

	return 0;
}