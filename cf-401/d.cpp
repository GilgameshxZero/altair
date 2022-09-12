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

long long fact (long long x)
{
	if (x == 0)
		return 1;
	else return fact (x - 1) * x;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	string n;
	int m, y, cnt[128];
	long long x, ans = 0, mul = 1;
	stringstream ss;

	for (int a = 0;a < 128;a++)
		cnt[a] = 0;
	cin >> n >> m;

	y = 1;
	for (int a = 1;a <= n.length ();a++)
	{
		y *= a;
		cnt[n[a-1]]++;
	}

	for (int a = 0;a < 128;a++)
		if (cnt[a] != 0)
			mul *= fact (cnt[a]);

	for (int a = 0;a < y;a++)
	{
		if (n[0] != '0')
		{
			ss.clear ();
			ss << n;
			ss >> x;
			if (x % m == 0)
				ans++;
		}

		next_permutation (n.begin (), n.end ());
	}

	cout << ans / mul << "\n";

	return 0;
}