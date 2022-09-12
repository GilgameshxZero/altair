/*
ID: yangchess1
LANG: C++
PROB: sort3
*/

/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

Backup this program every so often in the Backup files in case something goes wrong later.

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

int main ()
{
	std::ifstream in ("sort3.in");
	std::ofstream out ("sort3.out");
	int n, arr[1000], over[3][3], cnt[3], ans = 0, k;
	
	in >> n;
	cnt[0] = cnt[1] = cnt[2] = 0;
	for (int a = 0;a < n;a++)
	{
		in >> arr[a];
		cnt[--arr[a]]++;
	}

	for (int a = 0;a < 3;a++)
		for (int b = 0;b < 3;b++)
			over[a][b] = 0;

	cnt[1] += cnt[0];
	cnt[2] += cnt[1];

	for (int a = 0;a < cnt[0];a++)
		over[0][arr[a]]++;
	for (int a = cnt[0];a < cnt[1];a++)
		over[1][arr[a]]++;
	for (int a = cnt[1];a < cnt[2];a++)
		over[2][arr[a]]++;

	for (int a = 0;a < 3;a++)
	{
		for (int b = 0;b < 3;b++)
		{
			if (a != b)
			{
				k = min (over[a][b], over[b][a]);
				ans += k;
				over[a][b] -= k;
				over[b][a] -= k;
			}
		}
	}

	for (int a = 0;a < 3;a++)
	{
		for (int b = 0;b < 3;b++)
		{
			for (int c = 0;c < 3;c++)
			{
				if (a == 0 && b == 2 && c == 1)
					a=a;
				if (a != b && b != c && a != c)
				{
					k = min (over[a][b], min (over[b][c], over[c][a]));
					ans += 2 * k;
					over[a][b] -= k;
					over[b][c] -= k;
					over[c][a] -= k;
				}
			}
		}
	}

	out << ans << "\n";
	out.close ();

	return 0;
}