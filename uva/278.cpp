#define _CRT_SECURE_NO_WARNINGS

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
	freopen ("input0.in", "r", stdin);
	freopen ("output.out", "w", stdout);
#endif

	int n;
	cin >> n;
	for (;n --> 0;)
	{
		char c;
		int x, y;
		cin >> c >> x >> y;

		if (c == 'r' || c == 'Q')
			cout << min (x, y) << "\n";
		if (c == 'K')
			cout << round (ceil (x / 2.0) * ceil (y / 2.0)) << "\n";
		if (c == 'k')
			cout << round (ceil (x * y / 2.0)) << "\n";
	}

	return 0;
}