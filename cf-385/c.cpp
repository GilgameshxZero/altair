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
#include <stack>
#include <string>
#include <vector>

using namespace std;

int n, m, cnt[10000001], f[10000001], pre[10000001];
bitset<10000001> prime;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;
	for (int a = 0, b;a < n;a++)
		cin >> b,
		cnt[b]++;
	cin >> m;

	prime.reset ();
	for (int a = 2;a <= 10000000;a++)
	{
		if (!prime[a])
		{
			f[a] = cnt[a];
			for (int b = 2 * a;b <= 10000000;b += a)
			{
				if (!prime[b])
					prime[b].flip ();
				f[a] += cnt[b];
			}
		}
		pre[a] = f[a] + pre[a - 1];
	}

	for (long long a = 0, b, c;a < m;a++)
	{
		cin >> b >> c;
		if (b > 10000000)
			b = 10000000;
		if (c > 10000000)
			c = 10000000;
		cout << pre[c] - pre[b - 1] << "\n";
	}

	return 0;
}