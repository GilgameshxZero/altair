#include <algorithm>
#include <bitset>
#include <cassert>
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
#include <limits>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int n, x[1000000], t[1000000];

long long CntInv (int f, int l)
{
	if (f == l - 1)
		return 0;

	long long mid = (f + l) / 2, r = CntInv (f, mid) + CntInv (mid, l);
	
	memcpy (t, x, sizeof (x));
	for (int a = f, b = mid, c = 0;c < l - f;c++)
	{
		if (a == mid)
			t[c + f] = x[b++];
		else if (b == l)
			t[c + f] = x[a++], r += (b - mid);
		else
			if (x[a] > x[b])
				t[c + f] = x[b++];
			else
				t[c + f] = x[a++], r += (b - mid);
	}
	memcpy (x, t, sizeof (x));

	return r;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;

	//basically count inversions
	for (int a = 0;a < n;a++)
		cin >> x[a];

	cout << CntInv (0, n) << "\n";
/*
	int ans = 0;
	for (int a = 0;a < n;a++)
		for (int b = 0;b < n - 1;b++)
			if (x[b] > x[b + 1])
				swap (x[b], x[b + 1]), ans++;
	cout << ans << "\n";
	*/

	return 0;
}