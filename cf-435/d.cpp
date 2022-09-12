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

const int MAXN = 405;
int n, m, prow[MAXN][MAXN], pcol[MAXN][MAXN], pd1[MAXN][MAXN], pd2[MAXN][MAXN], grid[MAXN][MAXN];
long long ans = 0;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	/*for (int a = 0;a < MAXN;a++)
		for (int b = 0;b < MAXN;b++)
			grid[a][b] = 1;*/

	cin >> n >> m;
	for (int a = 0;a < n;a++)
	{
		cin.get ();
		for (int b = 0;b < m;b++)
			grid[a + 1][b + 1] = cin.get () - '0';
	}

	memset (prow, 0, sizeof (prow));
	memset (pcol, 0, sizeof (pcol));
	memset (pd1, 0, sizeof (pd1));
	memset (pd2, 0, sizeof (pd2));

	for (int a = 1;a <= n;a++)
		for (int b = 1;b <= m;b++)
		{
			prow[a][b] = grid[a][b] + prow[a][b - 1];
			pcol[a][b] = grid[a][b] + pcol[a - 1][b];
			pd1[a][b] = grid[a][b] + pd1[a - 1][b - 1];
			pd2[a][b] = grid[a][b] + pd2[a - 1][b + 1];
		}

	/*for (int a = 1;a <= n;a++)
	{
		for (int b = 1;b <= m;b++)
			cout << pd2[a][b];
		cout << "\n";
	}*/

	for (int a = 1;a <= n;a++)
		for (int b = 1;b <= m;b++)
			if (grid[a][b] == 0)
			{
				for (int h = 1;a - h > 0 && b - h > 0 && b + h <= m;h++)
					if (grid[a - h][b - h] == 0 && grid[a - h][b + h] == 0)
					{
						if (prow[a - h][b + h] - prow[a - h][b - h - 1] == 0)
							ans++;
					}
					else
						break;
				for (int h = 1;a - h > 0 && a + h <= n && b + h <= m;h++)
					if (grid[a - h][b + h] == 0 && grid[a + h][b + h] == 0)
					{
						if (pcol[a + h][b + h] - pcol[a - h - 1][b + h] == 0)
							ans++;
					}
					else
						break;
				for (int h = 1;a + h <= n && b - h > 0 && b + h <= m;h++)
					if (grid[a + h][b - h] == 0 && grid[a + h][b + h] == 0)
					{
						if (prow[a + h][b + h] - prow[a + h][b - h - 1] == 0)
							ans++;
					}
					else
						break;
				for (int h = 1;a - h > 0 && a + h <= n && b - h > 0;h++)
					if (grid[a - h][b - h] == 0 && grid[a + h][b - h] == 0)
					{
						if (pcol[a + h][b - h] - pcol[a - h - 1][b - h] == 0)
							ans++;
					}
					else
						break;

				for (int h = 1;a - h > 0 && b - h > 0;h++)
					if (grid[a - h][b] == 0 && grid[a][b - h] == 0)
					{
						if (pd2[a][b - h] - pd2[a - h - 1][b + 1] == 0)
							ans++;
					}
					else
						break;
				for (int h = 1;a - h > 0 && b + h <= m;h++)
					if (grid[a - h][b] == 0 && grid[a][b + h] == 0)
					{
						if (pd1[a][b + h] - pd1[a - h - 1][b - 1] == 0)
							ans++;
					}
					else
						break;
				for (int h = 1;a + h <= n && b + h <= m;h++)
					if (grid[a + h][b] == 0 && grid[a][b + h] == 0)
					{
						if (pd2[a + h][b] - pd2[a - 1][b + h + 1] == 0)
							ans++;
					}
					else
						break;
				for (int h = 1;a + h <= n && b - h > 0;h++)
					if (grid[a + h][b] == 0 && grid[a][b - h] == 0)
					{
						if (pd1[a + h][b] - pd1[a - 1][b - h - 1] == 0)
							ans++;
					}
					else
						break;
			}

	cout << ans << "\n";

	return 0;
}