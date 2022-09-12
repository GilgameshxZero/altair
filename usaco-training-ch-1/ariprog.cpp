/*
ID: yangchess1
LANG: C++
PROB: ariprog
*/

/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

Backup this program every so often in the Backup files in case something goes wrong later.

Max's and mins: numeric_limits<type_name>::min().
*/

//So this is probably pretty efficient.

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

const int MAXBISQUARE	= 125000; //250*250 + 1.
const int MAXANS		= 10000;

std::bitset<MAXBISQUARE + 1> bsquare; //Whether a number is a bisquare. All bits are init to 0. Kind of confusing with least sig/most sig.
std::pair<int, int> ans[MAXANS];

bool Comp (std::pair<int, int> a, std::pair<int, int> b)
{
	if (a.second < b.second || a.second == b.second && a.first < b.first)
		return true;

	return false;
}

int main ()
{
	std::ifstream in ("ariprog.in");
	std::ofstream out ("ariprog.out");
	int len, sqmax, cans = 0;
	int a, b, c;

	in >> len >> sqmax;
	in.close ();

	//Calculate which numbers are bisquares in the range [0, 125000].
	for (a = 0;a <= sqmax;a++)
		for (b = a;b <= sqmax;b++)
			bsquare[a * a + b * b] = 1;

	//Loop through every bisquare and distance.
	for (a = 0;a <= MAXBISQUARE;a++)
	{
		if (bsquare[a] == 0)
			continue;

		for (b = (MAXBISQUARE - a) / (len - 1);b > 0;b--) //Calculate max distance to acheive sequence of required length, and test all sequences with distances <= that max.
		{
			for (c = 1;c < len;c++) //Verify each element in sequence.
			{
				if (bsquare[a + c * b] == 0)
					break;
			}

			if (c == len)
			{
				ans[cans].first = a;
				ans[cans++].second = b;
			}
		}
	}

	std::sort (ans, ans + cans, Comp);

	if (cans == 0)
		out << "NONE\n";
	else
		for (a = 0;a < cans;a++)
			out << ans[a].first << " " << ans[a].second << "\n";

	out.close ();

	return 0;
}