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

const int MOD = 1e9+7;

//2, 3, 1
//0, -1, 100000006
//f(x + 1) = f(x - 1) - f(x) = -f(x) + f (x - 1).
//F(y) = F(y + 2) - F(y).
//F(a, b, x) = a * f(x - 1) + b * f(x - 2)
//1, 1, 2, 3, 5, 8
//a = -1 * given, b = 1 * given

//2, 3, 1, -2, -3, -1, 2
//x, y, y - x, -x, -y, x - y, x, y

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	long long x, y, n;
	cin >> x >> y >> n;
	
	n = (n - 1) % 6;
	long long a[6];
	a[0] = (x + MOD) % MOD;
	a[1] = (y + MOD) % MOD;
	a[2] = (y - x + MOD) % MOD;
	a[3] = (-x + MOD) % MOD;
	a[4] = (-y + MOD) % MOD;
	a[5] = (x - y + MOD) % MOD;

	cout << (a[n] + MOD) % MOD << "\n";

	return 0;
}