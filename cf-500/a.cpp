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

	int n, t;
	cin >> n >> t;

	vector<int> x (n);
	for (int a = 0;a < n;a++)
		cin >> x[a];

	int loc = 0;
	while (loc < t - 1)
		loc = loc + x[loc];
	if (loc == t - 1)
		cout << "YES\n";
	else
		cout << "NO\n";

	return 0;
}