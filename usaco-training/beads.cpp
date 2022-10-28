/*
ID: yangchess1
LANG: C++
PROB: beads
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
	std::ifstream in ("beads.in");
	std::ofstream out ("beads.out");
	string beads;
	int n, ans = 0;

	in >> n >> beads;

	//Try every breaking spot.
	char x;

	for (int a = 0, b, c, t1, t2;a < n;a++)
	{
		t1 = t2 = 0; //Bead counter.

		//Right side.
		for (b = a, x = 'w';b < n + a;b++, t1++)
			if ((beads[b % n] == 'r' && x == 'b') || (beads[b % n] == 'b' && x == 'r')) //Use mods to 'loop' around.
				break;
			else if (x == 'w')
				x = beads[b % n];

		//Left side.
		for (c = a - 1, x = 'w';c > a - 1 - n;c--, t2++)
			if ((beads[(c + n) % n] == 'r' && x == 'b') || (beads[(c + n) % n] == 'b' && x == 'r'))
				break;
			else if (x == 'w')
				x = beads[(c + n) % n];

		//Did we double count beads?
		if (t1 + t2 > n)
			t1 = n - t2; //If so, that means we can reach all the beads.

		ans = max (t1 + t2, ans);
	}

	out << ans << "\n";

	return 0;
}