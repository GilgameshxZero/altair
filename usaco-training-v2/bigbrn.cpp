/*
ID: yangchess1
PROG: bigbrn
LANG: C++
*/
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
#include <string>
#include <vector>

using namespace std;

//DP with lower right corner.
//Last seen tree on row/col.

int n, t, dp[1001][1001], 
	row[1001][1001], col[1001][1001]; //# of squares from last seen tree on row/col, counting from the left or the top.
bool tree[1001][1001];

int main ()
{
	ios_base::sync_with_stdio (false);
	std::freopen ("bigbrn.in", "r", stdin);
	std::freopen ("bigbrn.out", "w", stdout);

	cin >> n >> t;
	memset (tree, 0, sizeof (tree));
	for (int a = 0;a < t;a++)
	{
		int b, c;
		cin >> b >> c;
		tree[b][c] = true;
	}

	memset (dp, 0, sizeof (dp));
	memset (row, 0, sizeof (row));
	memset (col, 0, sizeof (col));

	//Init row and col arrays.
	for (int a = 1;a <= n;a++)
	{
		for (int b = 1;b <= n;b++)
		{
			row[a][b] = !tree[a][b] * (row[a][b - 1] + 1);
			col[a][b] = !tree[a][b] * (col[a - 1][b] + 1);
		}
	}

	int ans = 0;
	for (int a = 1;a <= n;a++)
	{
		for (int b = 1;b <= n;b++)
		{
			dp[a][b] = min (dp[a - 1][b - 1] + 1, min (row[a][b], col[a][b]));
			ans = max (ans, dp[a][b]);
		}
	}

	cout << ans << "\n";

	return 0;
}