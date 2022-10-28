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
	std::ifstream in ("cowrun.in");
	std::ofstream out ("cowrun.out");
	int ccow, cow_pos[1000];

	in >> ccow;

	for (int a = 0;a < ccow;a++)
		in >> cow_pos[a];

	in.close ();

	//Start a DP solution, DPing on time.

	return 0;
}