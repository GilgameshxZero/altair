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

	ll x[3];
	cin >> x[0] >> x[1] >> x[2];
	sort (x, x + 3, greater<ll>());

	if (x[0] - x[1] >= x[1] - x[2])
		cout << x[1] - x[2] + 2 * min (x[2], (x[0] - 2 * x[1] + x[2]) / 3) + (x[2] - min (x[2], (x[0] - 2 * x[1] + x[2]) / 3));
	else
		cout << x[0] - x[1] + (2 * x[1] - x[0] - x[2]) / 3 * 2 + x[2] + ((2 * x[1] - x[0] - x[2]) % 3 == 2 ? 1 : 0);

	return 0;
}