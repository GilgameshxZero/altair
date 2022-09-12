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

	string s, t;
	cin >> s >> t;

	//KMP find all occurences: failure func
	vector<int> ff;
	ff.resize (t.length () + 1);
	ff[0] = ff[1] = 0;
	for (int a = 2, b;a < ff.size ();a++)
	{
		b = ff[a - 1];
		while (true)
		{
			if (t[b] == t[a - 1])
			{
				ff[a] = b + 1;
				break;
			}
			else if (b == 0)
			{
				ff[a] = 0;
				break;
			}
			else
				b = ff[b];
		}
	}

	//get all occurences
	vector<int> occ; //1-indexed final char occ
	for (int b = 0, c = 0;b < s.length ();)
	{
		if (s[b] == t[c])
		{
			b++;
			c++;
			if (c == t.length ())
			{
				occ.push_back (b);
				c = ff[c];
			}
		}
		else if (c != 0)
			c = ff[c];
		else
			b++;
	}

	//DP with acc pre sum and 1-index
	vector<long long> dp (s.length () + 1), pre (s.length () + 1), adiff (s.length () + 1);
	const int MOD = 1e9+7;
	dp[0] = pre[0] = adiff[0] = 0;
	for (int a = 1, b = 0;a <= s.length ();a++)
	{
		if (b < occ.size () && occ[b] == a) //case 2
		{
			b++;
			dp[a] = (a + 1 - t.length () + adiff[a - t.length ()]) % MOD;
			pre[a] = (pre[a - 1] + dp[a]) % MOD;
			adiff[a] = (adiff[a - 1] + pre[a]) % MOD;
		}
		else
		{
			dp[a] = dp[a - 1];
			pre[a] = (pre[a - 1] + dp[a]) % MOD;
			adiff[a] = (adiff[a - 1] + pre[a]) % MOD;
		}
	}

	cout << pre[s.length ()] << "\n";

	return 0;
}