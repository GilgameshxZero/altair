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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n, m;
	cin >> n >> m;
	int x[100];
	for (int a = 0;a < n;a++)
		cin >> x[a];
	int last = -1, y[100];
	memset (y, 0, sizeof (y));
	for (int a = 0;a < 100;a++)
		for (int b = 0;b < n;b++)
			if (y[b] < x[b])
				y[b] += m, last = b;

	cout << last + 1 << "\n";

	return 0;
}