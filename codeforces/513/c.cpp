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

typedef long long ll;

double Prob (pair<int, int> r, int x)
{
	if (x < r.first)
		return 0;
	else if (x >= r.second)
		return 1;
	return (double)(x - r.first + 1) / (r.second - r.first + 1);
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int N;
	pair<int, int> range[5];
	cin >> N;
	for (int a = 0;a < N;a++)
		cin >> range[a].first >> range[a].second;

	double ans = 0, p, q;
	for (int a = 0;a < N;a++)
	{
		for (int b = 0;b < N;b++)
		{
			if (a == b)
				continue;

			//a is second highest, b wins
			for (int c = range[a].first;c <= range[a].second;c++)
			{
				p = 1 - Prob (range[b], c - 1);
				q = 1;
				for (int d = 0;d < N;d++)
				{
					if (d == a || d == b)
						continue;
					q = q * Prob (range[d], c);
				}
				ans += q * p * c / (range[a].second - range[a].first + 1);
			}
		}
	}

	cout << ans;

	return 0;
}