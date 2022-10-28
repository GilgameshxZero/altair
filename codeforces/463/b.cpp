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

int h[100001];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n, en = 0, ans = 0;
	cin >> n;
	h[0] = 0;
	for (int a = 1;a <= n;a++)
		cin >> h[a];

	for (int a = 0;a < n;a++)
	{
		en += h[a] - h[a + 1];

		if (en < 0)
		{
			ans -= en;
			en = 0;
		}
	}

	cout << ans << "\n";

	return 0;
}