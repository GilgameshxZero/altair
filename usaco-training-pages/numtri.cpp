/*
ID: yangchess1
LANG: C++
PROB: numtri
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

int tri[1000][1000], sum[1000][1000];

int main ()
{
	std::ifstream in ("numtri.in");
	std::ofstream out ("numtri.out");
	int crows;
	int a, b, c;

	in >> crows;

	for (a = 0;a < crows;a++)
		for (b = 0;b <= a;b++)
			in >> tri[a][b];

	in.close ();

	//Begin DP.
	sum[0][0] = tri[0][0];

	for (a = 1;a < crows;a++)
	{
		for (b = 0;b <= a;b++)
		{
			if (b == 0 || sum[a - 1][b] > sum[a - 1][b - 1])
				sum[a][b] = sum[a - 1][b] + tri[a][b];
			else
				sum[a][b] = sum[a - 1][b - 1] + tri[a][b];
		}
	}

	for (a = 0, c = 0;a < crows;a++)
		if (sum[crows - 1][a] > c)
			c = sum[crows - 1][a];

	out << c << "\n";
	out.close ();

	return 0;
}