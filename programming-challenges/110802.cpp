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

const int SPACE = 103831, HASH = 97;
string sol;
int grid[4][4];
bool vis[SPACE];

int Hash ()
{
	int r = 0;
	for (int a = 0;a < 4;a++)
		for (int b = 0;b < 4;b++)
			r = (r * HASH + grid[a][b]) % SPACE;

	return r;
}

bool DFS (int level)
{
	if (level == 46)
		return false;

	int h = Hash ();
	if (vis[h])
		return false;
	vis[h] = true;

	bool flag = true;
	for (int a = 0;a < 4;a++)
		for (int b = 0;b < 4;b++)
			if (a * 4 + b + 1 != 16 && grid[a][b] != a * 4 + b + 1)
				flag = false;

	if (flag == true)
		return true;

	int r, c;
	for (int a = 0;a < 4;a++)
		for (int b = 0;b < 4;b++)
			if (grid[a][b] == 0)
				r = a, c = b;

	bool ret = false;
	char move;
	if (r > 0)
	{
		swap (grid[r][c], grid[r - 1][c]);
		if (DFS (level + 1))
			ret = true,
			move = 'U';
		swap (grid[r][c], grid[r - 1][c]);
	}
	if (!ret && c > 0)
	{
		swap (grid[r][c], grid[r][c - 1]);
		if (DFS (level + 1))
			ret = true,
			move = 'L';
		swap (grid[r][c], grid[r][c - 1]);
	}
	if (!ret && r < 3)
	{
		swap (grid[r][c], grid[r + 1][c]);
		if (DFS (level + 1))
			ret = true,
			move = 'D';
		swap (grid[r][c], grid[r + 1][c]);
	}
	if (!ret && c < 3)
	{
		swap (grid[r][c], grid[r][c + 1]);
		if (DFS (level + 1))
			ret = true,
			move = 'R';
		swap (grid[r][c], grid[r][c + 1]);
	}

	if (ret == true)
		sol += move;

	vis[h] = false;

	return ret;
}

int main ()
{
	ios_base::sync_with_stdio (false);

	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int n;
	cin >> n;

	for (;n > 0;n--)
	{
		memset (vis, 0, sizeof (vis));
		for (int a = 0;a < 4;a++)
			for (int b = 0;b < 4;b++)
				cin >> grid[a][b];

		sol = "";
		DFS (0);
		
		if (sol == "")
			cout << "This puzzle is not solvable.\n";
		else
		{
			reverse (sol.begin (), sol.end ());
			cout << sol << "\n";
		}
	}

	return 0;
}