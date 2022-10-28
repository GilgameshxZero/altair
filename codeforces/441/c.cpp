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

	int n, m, k, curx = 0, cury = 1;
	vector< pair<int, int> > ans;
	cin >> n >> m >> k;

	for (int a = 0;a < k - 1;a++)
	{
		cout << "2 ";
		
		if (curx == m && cury % 2 == 1)
			cout << ++cury << " " << curx << " ";
		else if (curx == 1 && cury % 2 == 0)
			cout << ++cury << " " << curx << " ";
		else if (cury % 2 == 1)
			cout << cury << " " << ++curx << " ";
		else if (cury % 2 == 0)
			cout << cury << " " << --curx << " ";

		if (curx == m && cury % 2 == 1)
			cout << ++cury << " " << curx << "\n";
		else if (curx == 1 && cury % 2 == 0)
			cout << ++cury << " " << curx << "\n";
		else if (cury % 2 == 1)
			cout << cury << " " << ++curx << "\n";
		else if (cury % 2 == 0)
			cout << cury << " " << --curx << "\n";
	}

	while (cury <= n)
	{
		if (curx == m && cury % 2 == 1)
			ans.push_back (make_pair (++cury, curx));
		else if (curx == 1 && cury % 2 == 0)
			ans.push_back (make_pair (++cury, curx));
		else if (cury % 2 == 1)
			ans.push_back (make_pair (cury, ++curx));
		else if (cury % 2 == 0)
			ans.push_back (make_pair (cury, --curx));
	}

	cout << ans.size () - 1 << " ";
	for (int a = 0;a < ans.size () - 1;a++)
		cout << ans[a].first << " " << ans[a].second << " ";

	return 0;
}