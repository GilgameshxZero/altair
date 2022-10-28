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

	int n, x, y;
	x = y = 0;
	int i, j, k;
	cin >> i >> j >> k;
	x = i + j + k;
	cin >> i >> j >> k;
	y = i + j + k;
	cin >> n;
	while (x > 0)
		x -= 5, n--;
	while (y > 0)
		y -= 10, n--;

	if (n < 0)
		cout << "NO\n";
	else
		cout << "YES\n";

	return 0;
}