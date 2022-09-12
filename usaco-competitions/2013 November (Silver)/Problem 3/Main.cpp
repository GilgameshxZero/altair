#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

vector< pair<int, int> > target;
int dp[1000][1000];

int HBound (int start, int dist) //the next target after start with at least dist away from start
{
	for (int a = start;a < target.size ();a++)
		if (target[a].first - target[start].first >= dist)
			return a - start;

	return -1;
}

int LBound (int start, int dist) //the last target before start with at least dist away from start
{
	for (int a = start;a >= 0;a--)
		if (target[start].first - target[a].first >= dist)
			return start - a;

	return -1;
}

int main ()
{
	freopen ("pogocow.in", "r", stdin);
	freopen ("pogocow.out", "w", stdout);
	int n;
	cin >> n;

	int ans = 0;
	target.resize (n);
	for (int a = 0;a < n;a++)
		cin >> target[a].first >> target[a].second,
		ans = max (ans, target[a].second);
	sort (target.begin (), target.end ());

	//going right
	for (int a = n - 2;a >= 0;a--)
	{
		dp[a][0] = target[a].second;
		for (int b = 1, c;a + b < n;b++)
		{
			c = HBound (a + b, target[a + b].first - target[a].first);
			if (c != -1)
				dp[a][b] = target[a].second + dp[a + b][c];
			else
				dp[a][b] = target[a].second + target[a + b].second;
			ans = max (dp[a][b], ans);
		}
	}

	//going left
	dp[0][0] = -10000;
	for (int a = 1;a < n;a++)
	{
		dp[a][0] = target[a].second;
		for (int b = 1, c;a - b >= 0;b++)
		{
			c = LBound (a - b, target[a].first - target[a - b].first);
			if (c != -1)
				dp[a][b] = target[a].second + dp[a - b][c];
			else
				dp[a][b] = target[a].second + target[a - b].second;
			ans = max (dp[a][b], ans);
		}
	}

	cout << ans << "\n";

	return 0;
}