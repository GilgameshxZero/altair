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

//Erdos-Gallai (I coded it myself).

const int MAXCOW = 500;
vector<int> ans;
pair<int, int> deg[MAXCOW + 1];
int ccows, sum;

bool ErdosGallai (int ignore)
{
	if (sum % 2 != deg[ignore].first % 2)
		return false;

	for (int a = 0, x = 0, z;a <= ccows;a++)
	{
		if (a == ignore)
			continue;

		x += deg[a].first;
		z = 0;

		for (int b = a + 1;b <= ccows;b++)
		{
			if (b == ignore)
				continue;
			
			if (a < ignore)
				z += min (deg[b].first, a + 1);
			else
				z += min (deg[b].first, a);
		}

		if (a < ignore)
		{
			if (x > ((a + 1) * a + z))
				return false;
		}
		else
		{
			if (x > (a * (a - 1) + z))
				return false;
		}
	}

	return true;
}

bool Comp (pair<int, int> a, pair<int, int> b)
{
	return a.first > b.first;
}

int main ()
{
	std::ifstream in ("fcount.in");
	std::ofstream out ("fcount.out");

	in >> ccows;
	sum = 0;

	for (int a = 0;a <= ccows;a++)
	{
		in >> deg[a].first;
		deg[a].second = a + 1;
		sum += deg[a].first;
	}

	sort (deg, deg + ccows + 1, Comp);

	//Try removing each degree once and if it works, then record in answer vector.
	for (int a = 0;a <= ccows;a++)
	{
		if (ErdosGallai (a))
			ans.push_back (deg[a].second);
	}

	sort (ans.begin (), ans.end ());
	out << ans.size () << "\n";

	for (int a = 0;a < (int)ans.size ();a++)
		out << ans[a] << "\n";

	out.close ();

	return 0;
}