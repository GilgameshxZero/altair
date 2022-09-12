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

long long GCD (long long x, long long y)
{
	if (x == 0) return y;
	if (y == 0) return x;
	if (x >= y) return GCD (x % y, y);
	return GCD (y % x, x);
}

long long n, p[100000], sum = 0, pair_sum = 0, last = 0, dist, perm, g;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;
	for (int a = 0;a < n;a++)
		cin >> p[a];
	sort (p, p + n);

	last = p[0];
	sum += last;
	for (int a = 1;a < n;a++)
	{
		sum += p[a];
		pair_sum += (n - a) * a * (p[a] - last);
		last = p[a];
	}

	dist = 2 * sum + (n - 1) * 2 * pair_sum;
	perm = 1;

	for (int a = 2;a <= n;a++)
	{
		g = GCD (dist, a);
		dist /= g;
		perm *= (a / g);
	}

	cout << dist << " " << perm << "\n";

	return 0;
}