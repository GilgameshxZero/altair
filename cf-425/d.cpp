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

int n, ans;
bitset<100001> ex[100001];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;
	for (int a = 0, b, c;a < n;a++)
		cin >> b >> c,
		ex[b][c].flip ();

	cin.seekg (0);
	cin >> n;

	for (int a = 0, x, y;a < n;a++)
	{
		cin >> x >> y;
		int b = min (100000 - x, 100000 - y);
		for (int c = 1;c < b;c++)
			if (ex[x][y + c] && ex[x + c][y] && ex[x + c][y + c])
				ans++;
	}

	cout << ans << "\n";

	return 0;
}