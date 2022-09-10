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

	int n, m;
	while (cin >> n >> m)
	{
		if (n == 0 && m == 0)
			break;
		int k = min (n, m), j = max (n, m);
		if (k == 1)
			cout << j;
		else if (k == 2)
			cout << 4 * (j / 4) + min (2, j % 4) * 2;
		else if (k == 3 && n == m)
			cout << 5;
		else
			cout << (n * m + 1) / 2;
		cout << " knights may be placed on a " << n << " row " << m << " column board.\n";
	}

	return 0;
}