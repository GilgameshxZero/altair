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

int fact (int x)
{
	if (x == 0)
		return 1;
	else
		return x * fact (x - 1);
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	string t1, t2;
	cin >> t1 >> t2;

	int c1 = 0, c2 = 0, q = 0;
	for (int a = 0;a < t1.size ();a++)
	{
		c1 += (t1[a] == '+') * 2 - 1;
		if (t2[a] != '?')
			c2 += (t2[a] == '+') * 2 - 1;
		else
			q++;
	}

	int x = abs (c1 - c2);
	if (x > q || (q - x) % 2 == 1)
		cout << "0";
	else
		cout << fixed << setprecision (13) << (double)fact (q) / fact ((q - x) / 2) / fact (q - (q - x) / 2) / pow (2, q);

	return 0;
}