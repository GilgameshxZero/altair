#define _CRT_SECURE_NO_WARNINGS

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
	freopen ("input0.in", "r", stdin);
	freopen ("output.out", "w", stdout);
#endif

	int T;
	const double PI = 3.14159265358979323;
	cin >> T;

	for (int a = 0;a < T;a++)
	{
		int p, x, y;
		cin >> p >> x >> y;
		cout << "Case #" << a + 1 << ": ";
		
		if (sqrt ((50 - x) * (50 - x) + (50 - y) * (50 - y)) > 50)
			cout << "white";
		else if (p == 0)
			cout << "white";
		else if (p == 100)
			cout << "black";
		else
		{
			x -= 50;
			y -= 50;
			double deg = atan2 ((double)y, (double)x);
			deg = deg * 180 / PI;
			if (deg < 0)
				deg += 360;
			deg -= 90;
			if (deg < 0)
				deg += 360;
			deg = 360 - deg;
			double pct = p / 100.0 * 360;
			if (deg < pct)
				cout << "black";
			else
				cout << "white";
		}

		if (a != T - 1)
			cout << '\n';
	}

	return 0;
}