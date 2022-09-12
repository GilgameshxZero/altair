/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

When submitting the program, define DEBUG 0. When debugging, define DEBUG 1. In the program, for debugging information, use if (DEBUG){...} such that when it is submitted we don't have that code there.

Use this code to immediately terminate if the time is too much to handle: if (clock() > 0.95 * CLOCKS_PER_SEC) break;

Backup this program every so often in the Backup.txt files in case something goes wrong later.

Useful constants: INT_MAX, INT_MIN, UINT_MAX, LLONG_MIN, LLONG_MAX, ULLONG_MAX, _I64_MIN, _I64_MAX, _UI64_MAX.
*/

#include <algorithm>
#include <bitset>
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

const int	MAX_GROUP	= 250000;

vector<int> group [MAX_GROUP];

int main ()
{
	std::ifstream in ("invite.in");
	std::ofstream out ("invite.out");
	vector<int> cowset;
	int ccow, cgroup, prev_count = 0, notfound;
	int a, b, c, d;

	in >> ccow >> cgroup;

	for (a = 0;a < cgroup;a++)
	{
		in >> b;

		for (;b > 0;b--)
		{
			in >> c;
			group[a].push_back (c);
		}
	}

	cowset.push_back (1);

	//Straightforward.
	while (cowset.size () != prev_count)
	{
		prev_count = cowset.size ();

		//Go through the groups and see which additional cows need to be added.
		for (a = 0;a < cgroup;a++)
		{
			//Check the sizes first.
			d = group[a].size ();
			if (cowset.size () + 1 >= d)
			{
				//Are all except 1 of the elements of group[a] in cowset?
				notfound = 0;

				for (b = 0;b < d;b++)
				{
					//If the element isn't found.
					if (find (cowset.begin (), cowset.end (), group[a].at (b)) == cowset.end ())
					{
						notfound++;
						c = b;

						if (notfound >= 2)
							break;
					}
				}

				//Element c wasn't found.
				if (notfound == 1)
					cowset.push_back (group[a].at (c));
			}
		}
	}

	out << cowset.size () << "\n";
	out.close ();

	return 0;
}