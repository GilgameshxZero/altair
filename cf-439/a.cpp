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

	int n, d, t[100], x = 0, ans;

	cin >> n >> d;
	for (int a = 0;a < n;a++)
		cin >> t[a],
		x += t[a];

	x += (n - 1) * 10;
	ans = (n - 1) * 2;

	if (x > d)
		cout << "-1\n";
	else
		cout << ans + (d - x) / 5 << "\n";

	return 0;
}