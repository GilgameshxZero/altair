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
	cin >> n >> k;
	cout << k * (6 * n - 1) << "\n";

	for (int a = 0;a < n;a++)
		cout << k * (a * 6 + 1) << " " << k * (a * 6 + 2) << " " << k * (a * 6 + 3) << " " << k * (a * 6 + 5) << "\n";

	return 0;
}