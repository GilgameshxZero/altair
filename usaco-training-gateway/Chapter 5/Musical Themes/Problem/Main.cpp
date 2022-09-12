/*
ID: yangchess1
LANG: C++
PROB: theme
*/

/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

Backup this program every so often in the Backup files in case something goes wrong later.

Max's and mins: numeric_limits<type_name>::min().
*/

//If we have a theme starting at two places, then if we add another note to the beginning of both starting notes that are the same distance from their corresponding notes, then we can create a longer theme. So for each pair of starting notes we just need to see how many notes we can add that satisfy this. In other words, we want to find all pairs of notes, and see how far back we can trace melodies for that pair. Add a bit of optimization to this and it should work smoothly.

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
	std::ifstream in ("theme.in");
	std::ofstream out ("theme.out");
	int cnotes, length, longest = 4, notes[5000];

	in >> cnotes;

	for (int a = 0;a < cnotes;a++)
		in >> notes[a];

	in.close ();

	//Don't want to mess with border cases.
	if (cnotes < 10)
	{
		out << "0\n";
		out.close ();

		return 0;
	}

	for (int dist = 5;dist <= cnotes - 5;dist++)
	{
		length = 1;

		for (int a = cnotes - 1;a >= dist + 1;a--) //a: larger note in pair.
		{
			//See if the preceeding notes are equidistant from the current notes.
			if (notes[a - 1] - notes[a] == notes[a - dist - 1] - notes[a - dist])
			{
				length++;

				if (length > longest)
					longest = length;

				//If we have length equal the distance between starting points, then this length is maxed out, and we need to compute with a larger distance.
				if (length == dist)
					break;
			}
			else
				length = 1;
		}
	}

	if (longest < 5)
		out << '0';
	else
		out << longest;

	out << "\n";
	out.close ();

	return 0;
}