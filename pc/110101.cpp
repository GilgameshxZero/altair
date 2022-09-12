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

int clen[1000000], rmq[1000000][20];

int Len (long long x)
{
	if (x >= 1e6)
	{
		int c = 0;
		while (x != 1)
		{
			c++;
			if (x < 1e6)
				return c + Len (x) - 1;
			else if ((x & 1) == 0)
				x >>= 1;
			else
				x = x * 3 + 1;
		}

		return c;
	}
	if (clen[x] != 0) 
		return clen[x];
	else if ((x & 1) == 0)
		return clen[x] = 1 + Len (x >> 1);
	else
		return clen[x] = 1 + Len (x * 3 + 1);
}

int Bits (int x)
{
	for (int r = 0;;r++)
		if ((x >> r) == 0)
			return r;
}

int main ()
{
	ios_base::sync_with_stdio (false);

	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	clen[1] = 1;
	for (long long a = 2;a < 1e6;a++)
		Len (a);

	for (int a = 1;a < 1e6;a++)
		rmq[a][0] = clen[a];
	for (int a = 1;a < 20;a++)
		for (int b = 1;b + (1 << a) <= 1e6;b++)
			rmq[b][a] = max (rmq[b][a - 1], rmq[b + (1 << (a - 1))][a - 1]);

	int x, y;
	cin >> x >> y;
	while (!cin.fail ())
	{
		cout << x << " " << y << " ";
		if (x > y)
			swap (x, y);
		int b = Bits (y - x + 1) - 1;
		cout << max (rmq[x][b], rmq[y - (1 << b) + 1][b]) << "\n";
		cin >> x >> y;
	}

	return 0;
}