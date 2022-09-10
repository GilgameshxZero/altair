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

int clen[1000000];

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

int main ()
{
	ios_base::sync_with_stdio (false);

	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	clen[1] = 1;
	for (long long a = 2;a < 1e6;a++)
		Len (a);

	int x, y;
	cin >> x >> y;
	while (!cin.fail ())
	{
		int m = 0;
		for (int a = min (x, y);a <= max (x, y);a++)
			m = max (m, clen[a]);
		cout << x << " " << y << " " << m << "\n";
		cin >> x >> y;
	}

	return 0;
}