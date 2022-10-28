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

	int n, k;
	vector<int> x[3];

	cin >> n;
	for (int a = 0;a < n;a++)
	{
		cin >> k;
		x[k - 1].push_back (a + 1);
	}

	k = min (x[0].size (), min (x[1].size (), x[2].size ()));
	cout << k << "\n";
	for (int a = 0;a < k;a++)
		cout << x[0][a] << " " << x[1][a] << " " << x[2][a] << "\n";

	return 0;
}