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

//DP with prefix sums.

//#define DEBUG 0
#define DEBUG 1

struct CID
{
	int c[9]; //Count of each ID.

	CID ()
	{
		c[1] = c[2] = c[3] = c[4] = c[5] = c[6] = c[7] = c[8] = 0;
	}

	CID (int c1, int c2, int c3, int c4, int c5, int c6, int c7, int c8)
	{
		c[1] = c1;
		c[2] = c2;
		c[3] = c3;
		c[4] = c4;
		c[5] = c5;
		c[6] = c6;
		c[7] = c7;
		c[8] = c8;
	}
};

pair<int, int> cows[100000];
CID psum[100000];
int dp[100000];
int n, k;

bool ValidCID (CID x)
{
	int stand = 0, count = 0;

	for (int a = 1;a < 9;a++)
	{
		if (x.c[a] != 0)
			count++;

		if (stand == 0 && x.c[a] != 0)
			stand = x.c[a];
		else if (stand != x.c[a] && x.c[a] != 0)
			return false;
	}

	if (count >= k)
		return true;

	return false;
}

int main ()
{
	std::ifstream in ("fairphoto.in");
	std::ofstream out ("fairphoto.out");

	in >> n >> k;

	for (int a = 0;a < n;a++)
		in >> cows[a].first >> cows[a].second;

	in.close ();
	sort (cows, cows + n);

	//Prefix sums.
	psum[0].c[cows[0].second] = 1;

	for (int a = 1;a < n;a++)
	{
		psum[a] = psum[a - 1];
		psum[a].c[cows[a].second]++;
	}

	//DP.
	CID lcid;
	dp[0] = 0;

	for (int a = 1, b, max;a < n;a++)
	{
		max = 0;

		//dp[a] = max (dp[a - 1], any range from a to anything smaller).
		if (ValidCID (psum[a])) //b = 0.
		{
			dp[a] = cows[a].first - cows[0].first;
			continue;
		}
		else
		{
			lcid = psum[a];

			for (b = 1;cows[a].first - cows[b].first > dp[a - 1] && b < a;b++)
			{
				lcid.c[cows[b - 1].second]--;

				if (ValidCID (lcid))
				{
					dp[a] = cows[a].first - cows[b].first;
					max = -1;
					break;
				}
			}
		}

		if (max == 0)
			dp[a] = dp[a - 1];
	}

	if (dp[n - 1] == 0)
		out << "-1\n";
	else
		out << dp[n - 1] << "\n";

	out.close ();

	return 0;
}