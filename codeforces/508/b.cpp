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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	string n;
	cin >> n;

	int cdig[10];
	fill (cdig, cdig + 10, 0);
	for (int a = 0;a < n.length ();a++)
		cdig[n[a] - '0']++;

	if (cdig[0] + cdig[2] + cdig[4] + cdig[6] + cdig[8] == 0)
	{
		cout << "-1\n";
		return 0;
	}

	string ans = "-1";
	for (int a = 0;a < n.length () - 1;a++)
	{
		if (n[a] % 2 == 0)
		{
			if (n[a] < n[n.length () - 1])
			{
				ans = n;
				swap (ans[a], ans[ans.length () - 1]);
				break;
			}
		}
	}
	for (int a = n.length () - 1;a >= 0;a--)
	{
		if (n[a] % 2 == 0)
		{
			if (n[a] > n[n.length () - 1])
			{
				swap (n[a], n[n.length () - 1]);
				ans = max (ans, n);
				break;
			}
		}
	}
	cout << ans << "\n";

	return 0;
}