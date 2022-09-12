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

	vector<ll> li;

	for (int a = 2; a <= 63; a++)
	{
		for (int b = 0; b < a - 1; b++)
			li.push_back ((1ll << a) - (1ll << b) - 1);
	}

	ll lb, hb;
	cin >> lb >> hb;

	int ans = 0;
	for (int a = 0; a < li.size (); a++)
		if (li[a] >= lb && li[a] <= hb)
			ans++;

	cout << ans;

	return 0;
}