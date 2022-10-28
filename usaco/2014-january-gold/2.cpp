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

//Because I can't think of an algorithm that will actually work and program it in 48 minutes, I will just go with a basic algorithm of finding the largest square of either R's or S's, and output the side length of this square, because the tractor must finish with a square of a certain size. I'm sure I can get a few cases with this algorithm.

bool ok[100][100][100][100];

int main ()
{
	std::ifstream in ("skicourse.in");
	std::ofstream out ("skicourse.out");
	int m, n, ans = 1;
	char grid[100][100];
	
	in >> m >> n;

	for (int a = 0;a < m;a++)
	{
		in.get ();

		for (int b = 0;b < n;b++)
			grid[a][b] = in.get ();
	}

	in.close ();

	//DP the squares.
	for (int a = 0;a < m;a++)
		for (int b = 0;b < n;b++)
			ok[a][b][a][b] = true;

	for (int a = 0;a < m - 1;a++)
		for (int b = 0;b < n - 1;b++)
			for (int c = a + 1;c < m

	//Always stamp the largest square possible. Mark unstamped squares with '-', they can be anything.

	return 0;
}