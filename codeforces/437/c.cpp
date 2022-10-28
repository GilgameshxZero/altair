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
#include <string>
#include <vector>
#include <functional>
using namespace std;

struct Part
{
	int v;
	vector<int> edge;
};

bool Comp (Part x, Part y)
{
	return (x.v > y.v);
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n, m;
	long long ans = 0;
	Part part[1000];
	pair<int, int> temp[1000];

	cin >> n >> m;
	for (int a = 0;a < n;a++)
		cin >> part[a].v,
		temp[a] = make_pair (-part[a].v, a);
	for (int a = 0, b, c;a < m;a++)
		cin >> b >> c,
		part[b - 1].edge.push_back (c - 1),
		part[c - 1].edge.push_back (b - 1);

	sort (temp, temp + n);

	for (int i = 0, a = temp[i].second;i < n;i++, a = temp[i].second)
	{
		for (int b = 0;b < part[a].edge.size ();b++)
		{
			ans += part[part[a].edge[b]].v;
			for (int c = 0;c < part[part[a].edge[b]].edge.size ();c++)
				if (part[part[a].edge[b]].edge[c] == a)
				{
					part[part[a].edge[b]].edge.erase (part[part[a].edge[b]].edge.begin () + c);
					break;
				}

			part[a].edge.erase (part[a].edge.begin () + b--);
		}
	}

	cout << ans << "\n";

	return 0;
}