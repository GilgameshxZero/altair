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

int dp[10][1 << 9][1 << 3];

int main ()
{
	ios_base::sync_with_stdio (false);

	/*std::freopen ("bsudoku.txt", "r", stdin);
	std::freopen ("bsudoku.txt", "w", stdout);*/
	std::ifstream in ("bsudoku.in");
	std::ofstream out ("bsudoku.out");

	for (int c = 0;c < 10;c++)
		for (int a = 0;a < (1 << 9);a++)
			for (int b = 0;b < (1 << 3);b++)
				dp[c][a][b] = 10000;
	dp[0][0][0] = 0;

	bool col[9], three[3];
	int par, mask, t, t2, t3;
	for (int a = 1;a < 10;a++)
	{
		par = 0;
		mask = 0;
		for (int b = 0;b < 9;b++)
			mask <<= 1,
			mask += (in.get () == '1'),
			par ^= (mask & 1);
		in.get ();

		for (int b = 0;b < (1 << 9);b++)
		{
			for (int c = 0;c < (1 << 3);c++)
			{
				if (dp[a - 1][b][c] > 81)
					continue;

				if ((a == 4 || a == 7) && c != 0)
					continue;

				for (int d = 0;d < (1 << 9);d++) //expand out from dp[a - 1][b][c]
				{
					t3 = 0;
					for (int e = d, f = 0;f < 9;e >>= 1, f++)
						t3 += (e & 1);

					if ((t3 & 1) != par) //don't reduce t3 to 0 or 1, we use the t3 count later
						continue;

					t = mask ^ d;
					for (int e = b, f = 0;f < 9;e >>= 1, f++)
						col[8 - f] = (e & 1);
					for (int e = c, f = 0;f < 3;e >>= 1, f++)
						three[2 - f] = (e & 1);

					for (int e = t, f = 0;f < 9;e >>= 1, f++)
					{
						col[8 - f] ^= (e & 1);
						three[2 - (f / 3)] ^= (e & 1);
					}

					t = t2 = 0;
					for (int e = 0;e < 9;e++)
						t <<= 1,
						t += col[e];
					for (int e = 0;e < 3;e++)
						t2 <<= 1,
						t2 += three[e];

					dp[a][t][t2] = min (dp[a][t][t2], dp[a - 1][b][c] + t3);
				}
			}
		}
	}

	in.close ();
	out << dp[9][0][0] << "\n";
	out.close ();

	return 0;
}