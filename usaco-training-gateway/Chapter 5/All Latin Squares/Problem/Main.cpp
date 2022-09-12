/*
ID: yangchess1
PROG: latin
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

//-Inline?
//Assume first row/col are 1...N, then multiply answer by (N - 1)!
//Do not need to calculate last row.
//Symmetry on row 2.

int n; //Next row and col to fill out.
bool tar[8][8], tac[8][8]; //Taken in each row/col.
long long ans;

//Increment ans with current grid settings.
long long Calc (int r, int c)
{
	if (c == n + 1) return Calc (r + 1, 2);
	if (r == n) return 1;

	if (r == 2)
	{
		int calc[2] = {-1, -1}, rtrn = 0;
		for (int a = 1;a <= n;a++)
		{
			if (!tar[r][a] && !tac[c][a])
			{
				if (calc[a > c] < 0)
				{
					tar[r][a] = tac[c][a] = true;
					calc[a > c] = Calc (r, c + 1);
					rtrn += calc[a > c];
					tar[r][a] = tac[c][a] = false;
				}
				else
					rtrn += calc[a > c]; //Symmetry, don't calculate again.
			}
		}

		return rtrn;
	}
	else
	{
		int rtrn = 0;
		for (int a = 1;a <= n;a++)
		{
			if (!tar[r][a] && !tac[c][a])
			{
				tar[r][a] = tac[c][a] = true;
				rtrn += Calc (r, c + 1);
				tar[r][a] = tac[c][a] = false;
			}
		}

		return rtrn;
	}
}

int main ()
{
	ios_base::sync_with_stdio (false);
	std::freopen ("latin.in", "r", stdin);
	std::freopen ("latin.out", "w", stdout);

	cin >> n;
	//int c1 = clock ();

	memset (tar, 0, sizeof (tar));
	memset (tac, 0, sizeof (tac));

	for (int a = 2;a <= n;a++)
		tar[a][a] = tac[a][a] = true;

	ans = Calc (2, 2);

	for (int a = 2;a < n;a++)
		ans *= a;

	cout << ans << "\n";

	/*int c2 = clock ();
	double sec = (double)(c2 - c1) / CLOCKS_PER_SEC;

	cout << "TIME: " << sec << "\n";*/

	return 0;
}