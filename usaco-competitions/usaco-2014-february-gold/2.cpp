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

//P1: Brute force.

struct Bonus
{
	int req, events, bonus;
};

Bonus bonus[20];
int ccow, cbonus, pts[20][20], ev[20];

void FillEvents ()
{
	next_permutation (ev, ev + ccow);
}

int main ()
{
	std::ifstream in ("dec.in");
	std::ofstream out ("dec.out");

	in >> ccow >> cbonus;

	for (int a = 0;a < cbonus;a++)
		in >> bonus[a].events >> bonus[a].req >> bonus[a].bonus;

	for (int a = 0;a < ccow;a++)
		for (int b = 0;b < ccow;b++)
			in >> pts[a][b];

	in.close ();

	int total = 1;

	for (int a = 0;a < ccow;a++)
	{
		ev[a] = a;
		total *= (a + 1);
	}

	int point[21], ans = 0, t, s;
	
		point[0] = 0;

		for (int b = 0;b < ccow;b++)
			point[b + 1] = point[b] + pts[b][ev[b]];

		t = point[ccow];

		for (int b = 0;b < cbonus;b++)
		{
			s = 0;

			for (int c = 0;c < ccow;c++)
				if (ev[c] < bonus[b].req)
					s += pts[c][ev[c]];
			if (s >= bonus[b].events)
				t += bonus[b].bonus;
		}

		if (t > ans)
			ans = t;

	for (int a = 0;a < total;a++)
	{
		FillEvents ();
		point[0] = 0;

		for (int b = 0;b < ccow;b++)
			point[b + 1] = point[b] + pts[b][ev[b]];

		t = point[ccow];

		for (int b = 0;b < cbonus;b++)
		{
			s = 0;

			for (int c = 0;c < ccow;c++)
				if (ev[c] < bonus[b].events)
					s += pts[c][ev[c]];
			if (s >= bonus[b].req)
				t += bonus[b].bonus;
		}

		if (t > ans)
			ans = t;
	}

	out << ans << "\n";
	out.close ();

	return 0;
}