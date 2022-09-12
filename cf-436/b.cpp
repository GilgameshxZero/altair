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

int n, m, k, spi[2001];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n >> m >> k;
	memset (spi, 0, sizeof (spi));
	for (int a = 1;a <= n;a++)
	{
		cin.get ();
		for (int b = 1, c;b <= m;b++)
		{
			c = cin.get ();
			if (c == 'U')
			{
				if ((a - 1) % 2 == 0)
					spi[b]++;
			}
			else if (c == 'L')
			{
				if (b - a + 1 >= 1)
					spi[b - a + 1]++;
			}
			else if (c == 'R')
			{
				if (b + a - 1 <= m)
					spi[b + a - 1]++;
			}
		}
	}

	for (int a = 1;a <= m;a++)
		cout << spi[a] << " ";
	cout << "\n";

	return 0;
}