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

	int N;
	cin >> N;

	int lim = (1 << (1 + N)) - 1;
	vector<int> X (lim + 1);
	for (int a = 2;a <= lim;a++)
		cin >> X[a];

	int ans = 0;
	for (int a = lim;a >= 3;a -= 2)
	{
		ans += max (X[a], X[a - 1]) - min (X[a], X[a - 1]);
		X[a / 2] += max (X[a], X[a - 1]);
	}

	cout << ans << "\n";

	return 0;
}