//DP solution

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

int main ()
{
	ios_base::sync_with_stdio (false);

	freopen ("input0.txt", "r", stdin); freopen ("output.txt", "w", stdout);

	int t, n;
	pair<int, int> ans; //len, dist
	vector<int> x;
	vector< pair<int, int> > lis; //len, begin
	cin >> t;

	for (;t > 0;t--)
	{
		cin >> n;
		x.resize (n);
		lis.resize (n);
		for (int a = 0;a < n;a++)
			cin >> x[a];
		ans = make_pair (1, 0);
		for (int a = 0;a < n;a++)
		{
			lis[a] = make_pair (1, a);
			for (int b = 0;b < a;b++)
			{
				if (x[a] > x[b])
				{
					if (lis[a].first == lis[b].first + 1)
					{

					}
					else if (lis[a].first < lis[b].first + 1)
					{
						lis[a].first = lis[b].first + 1;
						lis[a].second = lis[b].second;
					}
				}
			}
			ans = max (ans, lis[a]);
		}
		cout << ans << "\n";
	}

	return 0;
}