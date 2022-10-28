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

	int n, m, curr = 0, ans = 0;

	cin >> n >> m;
	for (int a = 0, b;a < n;a++)
	{
		cin >> b;
		if (curr + b <= m)
			curr += b;
		else
			ans++,
			curr = b;
	}

	if (curr == 0)
		cout << ans << "\n";
	else
		cout << ans + 1 << "\n";

	return 0;
}