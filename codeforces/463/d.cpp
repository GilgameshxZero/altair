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

int n, k, edge[1000][1000], seq[5][1000], ans[1000], fans;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	memset (edge, 0, sizeof (edge));
	cin >> n >> k;
	for (int a = 0;a < k;a++)
		for (int b = 0;b < n;b++)
			cin >> seq[a][b],
			seq[a][b]--;

	for (int a = 0;a < k;a++)
		for (int b = n - 2;b >= 0;b--)
			for (int c = b + 1;c < n;c++)
				edge[seq[a][b]][seq[a][c]]++;

	ans[n - 1] = 1;
	for (int a = n - 2;a >= 0;a--)
	{
		ans[a] = 1;
		for (int b = a + 1;b < n;b++)
			if (edge[seq[0][a]][seq[0][b]] == k)
				ans[a] = max (ans[a], ans[b] + 1);
	}

	fans = 0;
	for (int a = 0;a < n;a++)
		fans = max (fans, ans[a]);
	cout << fans << "\n";

	return 0;
}