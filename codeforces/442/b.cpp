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

	double pct[100], s = 0, p = 1;
	int n;
	cin >> n;
	for (int a = 1;a <= n;a++)
		cin >> pct[a];

	sort (pct + 1, pct + n + 1);
	if (pct[n] == 1)
	{
		cout << "1\n";
		return 0;
	}

	for (int a = n;a >= 1;a--)
		if (s < 1)
			s += (pct[a] / (1 - pct[a])),
			p *= (1 - pct[a]);
		else
			break;

	cout << fixed << setprecision (12) << s * p << "\n";

	return 0;
}