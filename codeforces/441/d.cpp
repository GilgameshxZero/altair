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

//3 cases: trivial, join cycles/DSU, sel. sort.
int n, m, p[3001], par[3001], nswap, p2[3001];
vector< pair<int, int> > ans;

int Find (int x)
{
	if (par[x] < 0) return x;
	return par[x] = Find (par[x]);
}

int Size (int x)
{
	return -par[Find (x)];
}

void Union (int x, int y)
{
	int i = Find (x), j = Find (y);

	if (i == j) return;
	if (-par[i] >= -par[j])
		par[i] += par[j],
		par[j] = i;
	else
		par[j] += par[i],
		par[i] = j;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;
	for (int a = 1;a <= n;a++)
		cin >> p[a];
	cin >> m;

	memset (par, -1, sizeof (par));
	for (int a = 1, b;a <= n;a++)
	{
		if (Size (a) == 1)
		{
			b = a;
			while (p[b] != a)
			{
				b = p[b];
				Union (a, b);
				nswap++;
			}
		}
	}

	if (nswap == m)
	{
		cout << "0\n";
		return 0;
	}
	else if (nswap > m)
	{
		for (int a = 1, c = 0, low;a <= n && c < nswap - m;a++)
		{
			while (p[a] != a && c < nswap - m)
			{
				low = 100000;
				for (int b = p[a];b != a;b = p[b])
					low = min (low, b);

				ans.push_back (make_pair (a, low));
				p[a] ^= p[low];
				p[low] ^= p[a];
				p[a] ^= p[low];
				c++;
			}
		}

		cout << ans.size () << "\n";
		for (int a = 0;a < ans.size ();a++)
			cout << ans[a].first << " " << ans[a].second << " ";
	}
	else if (nswap < m)
	{
		for (int a = 1, c = 0;a <= n && c < m - nswap;a++)
		{
			for (int b = a + 1;b <= n && c < m - nswap;b++)
			{
				if (Find (a) != Find (b))
				{
					ans.push_back (make_pair (a, b));
					p[b] = p[a];
					p[a] = a;
					Union (a, b);
					c++;
				}
			}
		}

		cout << ans.size () << "\n";
		for (int a = 0;a < ans.size ();a++)
			cout << ans[a].first << " " << ans[a].second << " ";
	}

	return 0;
}