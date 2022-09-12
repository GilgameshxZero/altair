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

int main ()
{
	ios_base::sync_with_stdio (false);

	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int n, m, cas = 1;
	char grid[102][102];

	cin >> n >> m;
	while (n != 0)
	{
		if (cas != 1)
			cout << "\n\n";

		memset (grid, '.', sizeof (grid));
		for (int a = 1;a <= n;a++)
		{
			cin.get ();
			for (int b = 1;b <= m;b++)
				grid[a][b] = cin.get ();
		}

		for (int a = 1;a <= n;a++)
		{
			for (int b = 1;b <= m;b++)
			{
				if (grid[a][b] != '*')
				{
					int c = 0;
					c += grid[a - 1][b - 1] == '*';
					c += grid[a - 1][b] == '*';
					c += grid[a - 1][b + 1] == '*';
					c += grid[a][b - 1] == '*';
					c += grid[a][b + 1] == '*';
					c += grid[a + 1][b - 1] == '*';
					c += grid[a + 1][b] == '*';
					c += grid[a + 1][b + 1] == '*';
					grid[a][b] = c + '0';
				}
			}
		}

		cout << "Field #" << cas << ":";
		for (int a = 1;a <= n;a++)
		{
			cout << "\n";
			for (int b = 1;b <= m;b++)
				cout << grid[a][b];
		}

		cin >> n >> m;
		cas++;
	}

	cout << "\n";

	return 0;
}