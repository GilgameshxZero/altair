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

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int t;
	cin >> t;

	//gen primes < 31622.
	const int lim = 31622;
	bool comp[lim + 1];
	vector<int> prime;
	memset (comp, 0, sizeof (comp));
	for (int a = 2;a <= lim;a++)
	{
		if (!comp[a])
		{
			prime.push_back (a);
			for (int b = a * a;b <= lim;b += a)
				comp[b] = true;
		}
	}

	for (;t > 0;t--)
	{
		int x, y;
		bool f1;
		cin >> x >> y;

		if (x == 1) x = 2;

		for (int a = x;a <= y;a++)
		{
			f1 = true;
			for (int b = 0, c = 2 * 2;b < prime.size () && c <= a;b++, c += (prime[b] - prime[b - 1]) * (prime[b] + prime[b - 1]))
				if (a % prime[b] == 0)
				{
					f1 = false;
					break;
				}

			if (f1)
				cout << a << "\n";
		}

		cout << "\n";
	}

	return 0;
}