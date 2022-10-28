/*
ID: yangchess1
LANG: C++
PROB: castle
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

const int WMASK = 1 << 0;
const int NMASK = 1 << 1;
const int EMASK = 1 << 2;
const int SMASK = 1 << 3;

int r, c, 
	lroom, 
	lcr, lr, lc, ldir, 
	cid, fplan[50][50], id[50][50], roomsize[2501];

void Fill (int sr, int sc, int nid)
{
	id[sr][sc] = nid;
	roomsize[nid]++;

	if ((fplan[sr][sc] & NMASK) == 0 && id[sr - 1][sc] == 0)
		Fill (sr - 1, sc, nid);
	if ((fplan[sr][sc] & EMASK) == 0 && id[sr][sc + 1] == 0)
		Fill (sr, sc + 1, nid);
	if ((fplan[sr][sc] & SMASK) == 0 && id[sr + 1][sc] == 0)
		Fill (sr + 1, sc, nid);
	if ((fplan[sr][sc] & WMASK) == 0 && id[sr][sc - 1] == 0)
		Fill (sr, sc - 1, nid);
}

int main ()
{
	std::ifstream in ("castle.in");
	std::ofstream out ("castle.out");

	in >> c >> r;

	for (int a = 0;a < r;a++)
		for (int b = 0;b < c;b++)
			in >> fplan[a][b];

	in.close ();

	for (int a = 0;a < r;a++)
	{
		for (int b = 0;b < c;b++)
		{
			if (id[a][b] == 0)
			{
				Fill (a, b, ++cid);

				if (roomsize[cid] > lroom)
					lroom = roomsize[cid];
			}
		}
	}

	for (int b = 0;b < c;b++)
	{
		for (int a = r - 1;a >= 0;a--)
		{
			if (fplan[a][b] & NMASK && a != 0 && id[a - 1][b] != id[a][b])
			{
				if (roomsize[id[a - 1][b]] + roomsize[id[a][b]] > lcr)
				{
					lcr = roomsize[id[a - 1][b]] + roomsize[id[a][b]];
					lr = a;
					lc = b;
					ldir = NMASK;
				}
			}
			if (fplan[a][b] & EMASK && b != c - 1 && id[a][b + 1] != id[a][b])
			{
				if (roomsize[id[a][b + 1]] + roomsize[id[a][b]] > lcr)
				{
					lcr = roomsize[id[a][b + 1]] + roomsize[id[a][b]];
					lr = a;
					lc = b;
					ldir = EMASK;
				}
			}
		}
	}

	out << cid << "\n" << lroom << "\n" << lcr << "\n" << lr + 1 << " " << lc + 1 << " ";

	if (ldir == NMASK)
		out << "N\n";
	else
		out << "E\n";

	out.close ();

	return 0;
}