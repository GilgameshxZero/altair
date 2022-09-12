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

int ModExp (int x, int y, int mod)
{
	if (y == 1)
		return x;
	else if ((y & 1) == 0)
	{
		int k = ModExp (x, y >> 1, mod);
		return (int)(((ll)k * k) % mod);
	}
	else if ((y & 1) == 1)
	{
		int k = ModExp (x, y >> 1, mod);
		return (int)((ll)k * k % mod * x % mod);
	}
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int x;
	string s;
	cin >> x >> s;

	vector<int> cnt (26, 0);
	for (int a = 0;a < x;a++)
		cnt[s[a] - 'A']++;

	int mm = 0;
	for (int a = 0;a < 26;a++)
		mm = max (mm, cnt[a]);

	int dom = 0;
	for (int a = 0;a < 26;a++)
		if (mm == cnt[a])
			dom++;

	cout << ModExp (dom, x, 1e9+7);

	return 0;
}