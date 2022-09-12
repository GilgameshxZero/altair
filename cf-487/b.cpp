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

int n, s, l, x[100000], rmq[2][100000][18], cut[100000]; //min, max query

int Bits (int x)
{
	for (int r = 0;;r++)
		if ((x >> r) == 0)
			return r;
}

int MinQ (int a, int b)
{
	int k = Bits (b - a + 1) - 1;
	return min (rmq[0][a][k], rmq[0][b - (1 << k) + 1][k]);
}

int MaxQ (int a, int b)
{
	int k = Bits (b - a + 1) - 1;
	return max (rmq[1][a][k], rmq[1][b - (1 << k) + 1][k]);
}

int GetPos (int start)
{
	//bsearch
	int low = start, high = n, mid;
	while (low + 1 < high)
	{
		mid = (low + high) / 2;
		if (MaxQ (start, mid) - MinQ (start, mid) > s)
			high = mid;
		else
			low = mid;
	}

	return low;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n >> s >> l;
	for (int a = 0;a < n;a++)
		 cin >> x[a];

	for (int a = 0;a < n;a++)
		rmq[0][a][0] = rmq[1][a][0] = x[a];
	for (int a = 1;a < 18;a++)
		for (int b = 0;b + (1 << a) <= n;b++)
			rmq[0][b][a] = min (rmq[0][b][a - 1], rmq[0][b + (1 << (a - 1))][a - 1]),
			rmq[1][b][a] = max (rmq[1][b][a - 1], rmq[1][b + (1 << (a - 1))][a - 1]);

	int ans = 0;
	for (int a = 0, b, c, d, e;a < n;ans++)
	{
		b = GetPos (a);
		cut[ans] = a;

		c = a, d = b, e = ans;
		while (e >= 0 && d - c + 1 < l)
		{
			//try moving it back to fit l
			if (d - l + 1 >= 0 && MaxQ (d - l + 1, d) - MinQ (d - l + 1, d) <= s)
			{
				d = d - l;
				e--;
			}
			else
			{
				cout << "-1\n";
				return 0;
			}
			c = cut[e];
		}

		a = b + 1;
	}

	cout << ans;

	return 0;
}