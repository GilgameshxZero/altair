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

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	vector<int> ans;
	int n, v, low[500];

	cin >> n >> v;
	for (int a = 0, b;a < n;a++)
	{
		cin >> b;
		low[a] = 10000000;
		for (int c = 0, d;c < b;c++)
		{
			cin >> d;
			low[a] = min (low[a], d);
		}

		if (low[a] < v)
			ans.push_back (a + 1);
	}

	cout << ans.size () << "\n";
	for (int a = 0;a < ans.size ();a++)
		cout << ans[a] << " ";

	return 0;
}