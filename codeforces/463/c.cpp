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

ll x[2000][2000];
ll diag[2][4000], ans[2];
pair<int, int> pans[2];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n;
	cin >> n;
	for (int a = 0;a < n;a++)
		for (int b = 0;b < n;b++)
			cin >> x[a][b];

	memset (diag, 0, sizeof (diag));
	ans[0] = ans[1] = -1;

	for (int a = -(n - 1);a < n;a++)
	{
		int b = -a, c = a;
		int ta = max (0, a);
		b = max (0, b);
		for (;ta < n && b < n;ta++, b++)
			diag[0][c + n - 1] += x[ta][b];
	}
	for (int a = -(n - 1);a < n;a++)
	{
		int b = n - 1 + a, c = a;
		int ta = max (0, a);
		b = min (n - 1, b);
		for (;ta < n && b >= 0;ta++, b--)
			diag[1][c + n - 1] += x[ta][b];
	}

	for (int a = 0;a < n;a++)
		for (int b = 0;b < n;b++)
			if (ans[(a + b) & 1] < diag[0][-(b - a) + n - 1] + 
					diag[1][a + b] - x[a][b])
			{
				ans[(a + b) & 1] = diag[0][-(b - a) + n - 1] + 
					diag[1][a + b] - x[a][b];
				pans[(a + b) & 1] = make_pair (a + 1, b + 1);
			}

	cout << ans[0] + ans[1] << "\n";
	swap (pans[0], pans[1]);
	cout << pans[0].first << " " << pans[0].second << " " << pans[1].first << " " << pans[1].second << "\n";

	return 0;
}