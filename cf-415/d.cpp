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

const int MOD = 1e9+7;
int n, k, cnt[2001][2001];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	memset (cnt, 0, sizeof (cnt));
	cin >> n >> k;
	for (int a = 1;a <= n;a++)
		cnt[1][a] = 1;
	for (int a = 1;a < k;a++)
		for (int b = 1;b <= n;b++)
			for (int c = b;c <= n;c += b)
				cnt[a+1][c] = (cnt[a+1][c] + cnt[a][b]) % MOD;

	int ans = 0;
	for (int a = 1;a <= n;a++)
		ans = (ans + cnt[k][a]) % MOD;
	cout << ans << "\n";

	return 0;
}