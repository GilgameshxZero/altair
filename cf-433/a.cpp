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
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n, c[2];
	c[0] = c[1] = 0;
	cin >> n;
	for (int a = 0, b;a < n;a++)
	{
		cin >> b;
		c[b == 200]++;
	}
	
	if (c[0] % 2 == 0 && (c[1] % 2 == 0 || c[0] >= 2))
		cout << "YES\n";
	else
		cout << "NO\n";

	return 0;
}