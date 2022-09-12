#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

struct DPParam
{
	bool state; //0: end, 1: mid
	ll res_len; //if state == 0, then this is the len of path ending there
};

vector<int> edge[50000];
ll ans;
DPParam dp[50000];

void DFS (int cur, int par)
{
	if (edge[cur].size () == 1 && par != -1) //leaf
	{
		dp[cur].state = 1;
		dp[cur].res_len = 0;
		return;
	}

	int cmid = 0;
	ll low_end[2] = {-1, -1};
	vector<ll> end_len;
	for (int a = 0;a < edge[cur].size ();a++)
	{
		if (edge[cur][a] == par)
			continue;

		DFS (edge[cur][a], cur);
		if (dp[edge[cur][a]].state == 0)
		{
			end_len.push_back (dp[edge[cur][a]].res_len);
			if (low_end[1] == -1 || dp[edge[cur][a]].res_len < end_len[low_end[1]])
			{
				low_end[1] = end_len.size () - 1;
				if (low_end[0] == -1 || end_len[low_end[1]] < end_len[low_end[0]])
					swap (low_end[1], low_end[0]);
			}
		}
		else
			cmid++;
	}

	if (edge[cur].size () == 2 && par != -1) //1 child
	{
		dp[cur].state = 0;
		if (cmid == 1)
			dp[cur].res_len = 1;
		else
		{
			if (edge[cur][0] != par)
				dp[cur].res_len = dp[edge[cur][0]].res_len + 1;
			else
				dp[cur].res_len = dp[edge[cur][1]].res_len + 1;
		}
		return;
	}

	if (cmid >= 2)
	{
		dp[cur].state = 1;
		ans += 4 + (cmid - 2);
		for (int a = 0;a < end_len.size ();a++)
			ans += (end_len[a] + 1) * (end_len[a] + 1);
	}
	else if (cmid == 1)
	{
		dp[cur].state = 1;
		ans += (2 + end_len[low_end[0]]) * (2 + end_len[low_end[0]]);
		for (int a = 0;a < end_len.size ();a++)
			if (a != low_end[0])
				ans += (1 + end_len[a]) * (1 + end_len[a]);
	}
	else //cmid == 0
	{
		dp[cur].state = 1;
		ans += (2 + end_len[low_end[1]] + end_len[low_end[0]]) * (2 + end_len[low_end[1]] + end_len[low_end[0]]);
		for (int a = 0;a < end_len.size ();a++)
			if (a != low_end[0] && a != low_end[1])
				ans += (1 + end_len[a]) * (1 + end_len[a]);
	}
}

int main ()
{
	freopen ("solder.in", "r", stdin);
	freopen ("solder.out", "w", stdout);

	int N;
	cin >> N;

	for (int a = 0, b, c;a < N - 1;a++)
	{
		cin >> b >> c;
		edge[b - 1].push_back (c - 1);
		edge[c - 1].push_back (b - 1);
	}

	DFS (0, -1);

	if (dp[0].state == 0)
		ans += (dp[0].res_len * dp[0].res_len);

	cout << ans << "\n";

	return 0;
}