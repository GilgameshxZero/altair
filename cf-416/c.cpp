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

struct Book
{
	int c, p, num;
};

int dp[1001][1001], n, k, src[1001][1001];
vector< pair<int, int> > ans;
pair<int, int> r[1001];
Book book[1001];

bool BComp (Book x, Book y)
{
	return (x.c < y.c);
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;
	for (int a = 1;a <= n;a++)
		cin >> book[a].c >> book[a].p,
		book[a].num = a;
	sort (book + 1, book + n + 1, BComp);
	cin >> k;
	for (int a = 1;a <= k;a++)
		cin >> r[a].first,
		r[a].second = a;
	sort (r + 1, r + k + 1);

	memset (dp, 0, sizeof (dp));
	memset (src, -1, sizeof (src));
	for (int a = 1;a <= n;a++)
	{
		for (int b = 1;b <= k;b++)
		{
			dp[a][b] = dp[a - 1][b];
			src[a][b] = 1;
			if (dp[a][b - 1] > dp[a][b])
				dp[a][b] = dp[a][b - 1],
				src[a][b] = 2;
			if (r[b].first >= book[a].c && dp[a - 1][b - 1] + book[a].p > dp[a][b])
				dp[a][b] = dp[a - 1][b - 1] + book[a].p,
				src[a][b] = 3;
		}
	}

	int i = n, j = k;
	while (src[i][j] != -1)
	{
		if (src[i][j] == 1)
			i--;
		else if (src[i][j] == 2)
			j--;
		else
			ans.push_back (make_pair (book[i--].num, r[j--].second));
	}

	cout << ans.size () << " " << dp[n][k] << "\n";
	for (int a = 0;a < ans.size ();a++)
		cout << ans[a].first << " " << ans[a].second << "\n";

	return 0;
}