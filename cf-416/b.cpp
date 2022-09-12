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

int m, n, t[50000][5], av[50000][6];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> m >> n;
	for (int a = 0;a < m;a++)
		for (int b = 0;b < n;b++)
			cin >> t[a][b];

	memset (av, 0, sizeof (av));
	for (int a = 0;a < n;a++)
	{
		int c = 0;
		for (int b = 0;b < m;b++)
		{
			av[b][a + 1] = t[b][a] + max (av[b][a], c);
			c = av[b][a + 1];
		}
	}

	for (int a = 0;a < m;a++)
		cout << av[a][n] << " ";

	return 0;
}