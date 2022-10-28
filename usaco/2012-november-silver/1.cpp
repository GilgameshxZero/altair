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

int main ()
{
	std::ifstream in ("clumsy.in");
	std::ofstream out ("clumsy.out");
	string seq;
	int offset = 0, ans = 0;

	in >> seq;
	in.close ();

	//Calculate offsets.
	for (int a = 0;a < seq.size ();a++)
	{
		if (seq[a] == '(')
			offset++;
		else
			offset--;

		if (offset < 0)
		{
			//Change a parenthesis.
			offset += 2;
			ans++;
		}
	}

	//If we do not end at 0.
	if (offset != 0)
		ans += offset / 2;

	out << ans << "\n";
	out.close ();

	return 0;
}