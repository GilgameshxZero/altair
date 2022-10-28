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

	int n, k, x[200], ans = -100000000, sum;
	vector<int> cur, other;

	cin >> n >> k;
	for (int a = 0;a < n;a++)
		cin >> x[a];

	for (int a = 0;a < n;a++)
	{
		for (int b = a;b < n;b++)
		{
			cur.clear ();
			sum = 0;
			for (int c = a;c <= b;c++)
				cur.push_back (x[c]),
				sum += x[c];
			sort (cur.begin (), cur.end ());
			other.clear ();
			for (int c = 0;c < a;c++)
				other.push_back (x[c]);
			for (int c = b + 1;c < n;c++)
				other.push_back (x[c]);
			sort (other.begin (), other.end (), greater<int>());

			for (int c = 0;c < k && c < cur.size () && c < other.size ();c++)
				if (other[c] > cur[c])
					sum += other[c] - cur[c];
				else
					break;

			ans = max (ans, sum);
		}
	}

	cout << ans << "\n";

	return 0;
}