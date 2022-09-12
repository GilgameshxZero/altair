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

map<int, long long> query;
int n, gcd[20][100000], q;

int GCD (int a, int b)
{
	if (a < b)
		swap (a, b);
	while (a != 0 && b != 0)
		a %= b,
		swap (a, b);
	return a;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;
	for (int a = 0;a < n;a++)
		cin >> gcd[0][a];

	//sparse table
	for (int a = 1;a < 20;a++)
		for (int b = 0;b + (1 << a) <= n;b++)
			gcd[a][b] = GCD (gcd[a - 1][b], gcd[a - 1][b + (1 << (a - 1))]);

	//bsearch for gcd intervals starting at every position
	for (int a = 0;a < n;a++)
	{
		int b =	0, c = a;
		for (;c < n;)
		{
			int d = c;
			b = GCD (b, gcd[0][c]);
			for (int e = 19;e >= 0;e--)
				if (d + (1 << e) <= n && gcd[e][d] % b == 0)
					d += (1 << e) - 1;
			query[b] += d - c + 1;
			c = d + 1;
		}
	}

	cin >> q;
	for (int a = 0, b;a < q;a++)
		cin >> b,
		cout << query[b] << "\n";

	return 0;
}