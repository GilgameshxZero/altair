/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

When submitting the program, define DEBUG 0. When debugging, define DEBUG 1. In the program, for debugging information, use if (DEBUG){...} such that when it is submitted we don't have that code there.

Backup this program every so often in the Backup.txt files in case something goes wrong later.

Max's and mins: numeric_limits<type_name>::min().
*/

#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//#define DEBUG 0
#define DEBUG 1

const int MAXK = 16, MAXN = 100000, MAXS = 1 << 16;
int K, N, coin[MAXK], pur[MAXN], real_pre[MAXN + 1], dp[MAXS], *pre, money = 0, ans = -1;

int BSearch (int base, int begin, int end, int coin)
{
	if (begin + 1 == end)
		return begin;
	
	int a = (begin + end) / 2;
	if (pre[a] - pre[base] > coin)
		return BSearch (base, begin, a, coin);
	
	return BSearch (base, a, end, coin);
}

int main ()
{
	std::ifstream in ("nochange.in");
	std::ofstream out ("nochange.out");

	pre = &real_pre[1];
	in >> K >> N;
	for (int a = 0;a < K;a++)
	{
		in >> coin[a];
		money += coin[a];
	}
	pre[-1] = 0;
	for (int a = 0;a < N;a++)
	{
		in >> pur[a];
		pre[a] = pre[a - 1] + pur[a];
	}
	in.close ();

	dp[0] = -1;
	for (int a = 1, t, t2;a < (1 << K);a++)
	{
		//Calculate leftover.
		t = 0;
		for (int b = 0;b < K;b++)
			if (a & (1 << b))
				t += coin[b];

		if (money - t < ans)
			continue;

		//Can subset pay?
		for (int b = 0;b < K;b++)
		{
			if (a & (1 << b))
			{
				//Binary search last purchase covered by subset, and replace if greater than records.
				t2 = dp[a & (~(1 << b))];
				dp[a] = max (dp[a], BSearch (t2, t2 + 1, N, coin[b]));
				
				//Check if this subset can pay.
				if (dp[a] == N - 1)
					ans = money - t;
			}
		}
	}

	out << ans << "\n";
	out.close ();

	return 0;
}