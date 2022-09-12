/*
ID: yangchess1
PROG: tour
LANG: C++
*/
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

//dp[i][j]: most cities visited starting at i, to the end city, then ending at j, counting all cities on the road, including i and j. dp[i][i] = 0 (except for n - 1, in which it is 1, and 0). dp of i from n - 1 to 0, and j is the same.
//use edges to construct dp recurrence. answer is in dp[0][0] - 1.

int main ()
{
	ios_base::sync_with_stdio (false);
	std::freopen ("tour.in", "r", stdin);
	std::freopen ("tour.out", "w", stdout);

	int n, m;
	cin >> n >> m;

	map<string, int> ref;
	for (int a = 0;a < n;a++)
	{
		string temp;
		cin >> temp;
		ref.insert (make_pair (temp, a));
	}

	vector<int> fly[100];
	for (int a = 0;a < m;a++)
	{
		string b, c;
		cin >> b >> c;
		int x, y;
		x = ref.find (b)->second;
		y = ref.find (c)->second;
		fly[x].push_back (y);
		fly[y].push_back (x);
	}

	int dp[100][100];
	memset (dp, -1, sizeof (dp));
	
	//outgoing from end city
	for (int a = 0;a < fly[n - 1].size ();a++)
		dp[n - 1][fly[n - 1][a]] = dp[fly[n - 1][a]][n - 1] = 2;

	for (int a = n - 1;a >= 0;a--)
	{
		for (int b = n - 1;b >= 0;b--)
		{
			if (a == b) continue;

			if (a < b)
				for (int c = 0;c < fly[a].size ();c++)
					if (fly[a][c] > a && fly[a][c] != b && dp[fly[a][c]][b] != -1)
						dp[a][b] = max (dp[a][b], dp[fly[a][c]][b] + 1);

			if (a > b)
				for (int c = 0;c < fly[b].size ();c++)
					if (fly[b][c] > b && fly[b][c] != a && dp[a][fly[b][c]] != -1)
						dp[a][b] = max (dp[a][b], dp[a][fly[b][c]] + 1);

			if (a == b && a != n - 1)
				dp[a][b]--;
		}
	}

	int ans = 1;
	for (int a = 0;a < fly[0].size ();a++)
		ans = max (ans, max (dp[fly[0][a]][0], dp[0][fly[0][a]]));
	cout << ans << "\n";
	
	return 0;
}