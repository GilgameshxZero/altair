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

int GCD (int x, int y)
{
	if (x == 0) return y;
	else if (y == 0) return x;
	else if (x >= y) return GCD (x % y, y);
	else if (x < y) return GCD (y % x, x);
}

int LCM (int x, int y)
{
	return x * y / GCD (x, y);
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int x, y, i, j;
	cin >> x >> y >> i >> j;
	int l = LCM (x, y);
	int a = (i - 1) / l, b = j / l;
	cout << b - a << "\n";

	return 0;
}