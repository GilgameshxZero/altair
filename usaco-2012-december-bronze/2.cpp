/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

When submitting the program, define DEBUG 0. When debugging, define DEBUG 1. In the program, for debugging information, use if (DEBUG){...} such that when it is submitted we don't have that code there.

Use this code to immediately terminate if the time is too much to handle: if (clock() > 0.95 * CLOCKS_PER_SEC) break;

Use the contest logger we made to log the contest.

Backup this program every so often in the Backup.txt files in case something goes wrong later.
*/

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//#define DEBUG 0
#define DEBUG 1

using namespace std;

#define INTINFINITY 100000000000;

double cost[2000][2000];
int ccow, origcost, powercost, cow[2000];

int QCompare (const void *a, const void *b)
{
	return (*reinterpret_cast<int *>(const_cast<void *>(a)) - *reinterpret_cast<int *>(const_cast<void *>(b)));
}

double GetCost (int start, int end)
{
	int a;
	double temp, min_cost = INTINFINITY;

	if (cost[start][end] != -1)
		return cost[start][end];
	
	for (a = start;a < end;a++)
	{
		if (GetCost (start, a) + GetCost (a + 1, end) < min_cost)
			min_cost = GetCost (start, a) + GetCost (a + 1, end);
	}

	temp = origcost + powercost * static_cast<float>(cow[start] + cow[end]) / 2;

	if (temp < min_cost)
		min_cost = temp;

	cost[start][end] = min_cost;
	return min_cost;
}

int main ()
{
	std::ifstream in ("wifi.in");
	std::ofstream out ("wifi.out");
	int a, b;

	for (a = 0;a < 2000;a++)
		for (b = 0;b < 2000;b++)
			cost[a][b] = -1;

	in >> ccow >> origcost >> powercost;

	for (a = 0;a < ccow;a++)
		in >> cow[a];

	in.close ();

	//Sort the cows.
	qsort (cow, ccow, sizeof (int), QCompare);

	for (a = 0;a < ccow;a++)
		cost[a][a] = origcost;

	out << GetCost (0, ccow - 1) << "\n";
	out.close ();

	return 0;
}