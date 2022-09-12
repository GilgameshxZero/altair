/*
ID: yangchess1
LANG: C++
PROB: job
*/

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

const int CMACHINE_MAX	= 200;
const int CJOB_MAX		= 1000;

int QSortComp (const void *a, const void *b)
{
  return (*static_cast<int *>(const_cast<void *>(a)) - *static_cast<int *>(const_cast<void *>(b)));
}

int main ()
{
	std::ifstream in ("job.in");
	std::ofstream out ("job.out");
	int cjob, ca, cb, finish_allA, finish_all, finish_a[CJOB_MAX], finish_b[CJOB_MAX], machineA_time[CMACHINE_MAX], machineB_time[CMACHINE_MAX], machineA_avail[CMACHINE_MAX], machineB_avail[CMACHINE_MAX];

	in >> cjob >> ca >> cb;

	for (int a = 0;a < ca;a++)
	{
		in >> machineA_time[a];
		machineA_avail[a] = 0;
	}

	for (int a = 0;a < cb;a++)
	{
		in >> machineB_time[a];
		machineB_avail[a] = 0;
	}

	in.close ();

	//Start a greedy solution increasing on the number of jobs.
	finish_allA = 0;
	finish_all = 0;

	//Calculate the time it takes to finish with all the A machines.
	for (int a = 0, c, d;a < cjob;a++)
	{
		finish_a[a] = INT_MAX;

		for (int b = 0;b < ca;b++)
		{
			c = machineA_avail[b] + machineA_time[b];

			if (c < finish_a[a])
			{
				finish_a[a] = c;
				d = b;
			}
		}

		//Mark that we used the bth machine A for job a.
		machineA_avail[d] += machineA_time[d];

		//Check if this is greater than our smallest time.
		if (finish_a[a] > finish_allA)
			finish_allA = finish_a[a];
	}

	//Calculate the time it will take to finish all the B machines (from the end of time).
	for (int a = 0, c, d;a < cjob;a++)
	{
		finish_b[a] = INT_MAX;

		for (int b = 0;b < cb;b++)
		{
			c = machineB_avail[b] + machineB_time[b];

			if (c < finish_b[a])
			{
				finish_b[a] = c;
				d = b;
			}
		}

		//Mark that we used the bth machine A for job a.
		machineB_avail[d] += machineB_time[d];
	}

	//We now have the fastest times it takes for all the jobs to get through step A, and separately step B. Pair them up, the shortest to the longest, and record the shortest time for output.
	qsort (finish_a, cjob, sizeof (int), QSortComp);
	qsort (finish_b, cjob, sizeof (int), QSortComp);

	for (int a = 0;a < cjob;a++)
	{
		if (finish_a[a] + finish_b[cjob - a - 1] > finish_all)
			finish_all = finish_a[a] + finish_b[cjob - a - 1];
	}

	out << finish_allA << " " << finish_all << "\n";
	out.close ();

	return 0;
}