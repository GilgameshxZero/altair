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
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//#define DEBUG 0
#define DEBUG 1

double num[100000], mse[100000], sum;
int n;

bool IsPossible (double ave)
{
	double max;

	mse[1] = max = num[1] - ave;

	for (int a = 1;a < n - 1;a++)
	{
		if (mse[a - 1] > 0)
			mse[a] = mse[a - 1] + num[a] - ave;
		else
			mse[a] = num[a] - ave;

		if (mse[a] > max)
			max = mse[a];
	}

	if (max >= sum - ave * n)
		return true;

	return false;
}

int main ()
{
	std::ifstream in ("sabotage.in");
	std::ofstream out ("sabotage.out");
	double low = 0, high = 0;

	in >> n;

	for (int a = 0;a < n;a++)
	{
		in >> num[a];
		sum += num[a];

		if (num[a] > high)
			high = num[a];
	}

	in.close ();

	//Binary search with low and high bounds.
	while (high - low > 0.0001)
	{
		if (IsPossible ((high - low) / 2 + low))
			high = (high - low) /2 + low;
		else
			low = (high - low) / 2 + low;
	}

	out.precision (3);
	out << fixed << low << "\n";
	out.close ();

	return 0;
}