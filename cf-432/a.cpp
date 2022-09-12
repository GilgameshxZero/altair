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
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input2.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n, k, t[2000], a;
	cin >> n >> k;
	for (a = 0;a < n;a++)
	{
		cin >> t[a];
		if (t[a] + k > 5)
		{
			a--;
			n--;
		}
	}

	cout << a / 3 << "\n";

	return 0;
}