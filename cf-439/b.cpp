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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	long long n, x, c[100010], ans = 0;

	cin >> n >> x;
	for (int a = 0;a < n;a++)
		cin >> c[a];

	sort (c, c + n);

	for (int a = 0;a < n;a++)
	{
		ans += x-- * c[a];
		if (x == 0) x = 1;
	}

	cout << ans << "\n";

	return 0;
}