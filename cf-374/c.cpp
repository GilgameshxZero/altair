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

int n, m, cnt[1000][1000], id[1000][1000], cid, ans;
char grid[1000][1000];

int DFS (int x, int y, int pid, char nlet)
{
	if (id[x][y] == pid)
		return 1 << 29;
	
	id[x][y] = pid;
	char tlet;
	if (nlet == 'D') tlet = 'I';
	if (nlet == 'I') tlet = 'M';
	if (nlet == 'M') tlet = 'A';
	if (nlet == 'A') tlet = 'D';

	int r = 1;
	if (x > 0 && grid[x - 1][y] == nlet)
		r = max (r, 1 + DFS (x - 1, y, pid, tlet));
	if (y > 0 && grid[x][y - 1] == nlet)
		r = max (r, 1 + DFS (x, y - 1, pid, tlet));
	if (x < n - 1 && grid[x + 1][y] == nlet)
		r = max (r, 1 + DFS (x + 1, y, pid, tlet));
	if (y < m - 1 && grid[x][y + 1] == nlet)
		r = max (r, 1 + DFS (x, y + 1, pid, tlet));
	id[x][y] = 0;

	return r;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n >> m;
	for (int a = 0;a < n;a++)
	{
		cin.get ();
		for (int b = 0;b < m;b++)
			grid[a][b] = cin.get ();
	}

	for (int a = 0;a < n;a++)
		for (int b = 0;b < m;b++)
			if (grid[a][b] == 'D')
			{
				ans = max (ans, DFS (a, b, ++cid, 'I'));
			}

	if (ans >= 1 << 29)
		cout << "Poor Inna!\n";
	else if (ans < 4)
		cout << "Poor Dima!\n";
	else
		cout << ans / 4 << "\n";

	return 0;
}