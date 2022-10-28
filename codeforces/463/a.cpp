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

	int n, s, ans = -1;
	cin >> n >> s;

	s *= 100;
	for (int a = 0;a < n;a++)
	{
		int b, c;
		cin >> b >> c;
		b = b * 100 + c;

		if (b <= s)
		{
			ans = max (ans, (s - b) % 100);
		}
	}

	cout << ans << "\n";

	return 0;
}