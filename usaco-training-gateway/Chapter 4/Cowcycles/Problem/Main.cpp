/*
ID: yangchess1
LANG: C++
PROB: cowcycle
*/

/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

When submitting the program, define DEBUG 0. When debugging, define DEBUG 1. In the program, for debugging information, use if (DEBUG){...} such that when it is submitted we don't have that code there.

Use this code to immediately terminate if the time is too much to handle: if (clock() > 0.95 * CLOCKS_PER_SEC) break;

Backup this program every so often in the Backup.txt files in case something goes wrong later.

To access max's and min's for fundamental types, use std::numeric_limits<type>.max () or .min ().
*/

#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

//#define DEBUG 0
#define DEBUG 1

/*
List of optimizations:


*/

const int	MAX_FRONT_GEAR	= 5;
const int	MAX_REAR_GEAR	= 10;

int QSortComp (const void *a, const void *b)
{
	if ((*reinterpret_cast<double *>(const_cast<void *>(a)) - *reinterpret_cast<double *>(const_cast<void *>(b))) > static_cast<double>(0))
		return 1;
	
	return -1;
}

int main ()
{
	std::ifstream in ("cowcycle.in");
	std::ofstream out ("cowcycle.out");
	size_t size_double = sizeof (double);
	double mean, variance, sm_var, ratio[MAX_FRONT_GEAR * MAX_REAR_GEAR], diff[MAX_FRONT_GEAR * MAX_REAR_GEAR - 1];
	int cfront, crear, fsm, flg, rsm, rlg, fquit, rquit, front[MAX_FRONT_GEAR], rear[MAX_REAR_GEAR], max_front[MAX_FRONT_GEAR], max_rear[MAX_REAR_GEAR];
	double x;
	int a, b, c;

	if (DEBUG)
		cout << clock () << "\n";

	in >> cfront >> crear >> fsm >> flg >> rsm >> rlg;
	in.close ();

	//The problem suggests we do a complete search. Use a DFS, by choosing a complete gearing, and testing if it works. First, initialize the front and rear gearings to the END of the front and rear possible sets.
	for (a = 0, b = flg - cfront + a + 1;a < cfront;a++)
		front[a] = b++;

	for (a = 0, b = rlg - crear + a + 1;a < crear;a++)
		rear[a] = b++;

	sm_var = numeric_limits<double>::max ();
	fquit = fsm + cfront - 1;
	rquit = rsm + crear - 1;

	while (true)
	{
		//Check if this gearing of the front and rear has a 3x span from high gear to low gear. This is easy, because our gears are sorted. We only go on further if it has this property.
		if (static_cast<int>((static_cast<double>(front[cfront - 1]) / static_cast<double>(rear[0])) / (static_cast<double>(front[0]) / static_cast<double>(rear[crear - 1]))) >= 3)
		{
			//Here, we check if the variance is the smallest we have encountered. If so, record it for output later. First, calculate all the possible ratios.
			for (a = 0;a < cfront;a++)
				for (b = 0;b < crear;b++)
					ratio[a * crear + b] = static_cast<double>(front[a]) / static_cast<double>(rear[b]);

			//Sort the ratios.
			qsort (ratio, cfront * crear, size_double, QSortComp);

			//Calculate the differences, and their mean.
			mean = 0;

			for (a = 0,c = cfront * crear - 1;a < c;a++)
			{
				diff[a] = ratio[a + 1] - ratio[a];
				mean += diff[a];
			}

			mean /= c;

			//Calculate the variance.
			variance = 0;

			for (a = 0;a < c;a++)
			{
				x = diff[a] - mean;
				variance += x * x;
			}

			variance /= c;

			if (variance < sm_var)
			{	
				sm_var = variance;

				for (a = 0;a < cfront;a++)
					max_front[a] = front[a];

				for (a = 0;a < crear;a++)
					max_rear[a] = rear[a];
			}
		}
		else //If there is no 3x ratio, we can just skip this circulation of the last rear gear.
			rear[crear - 1] = rear[crear - 2] + 1;

		//Update gears to the next setting. Maintain that front[a] > front[a + 1], and same for the rear. We will not miss any, even with this property. If both gearings are at their last, then we can quit now.
		if (front[cfront - 1] == fquit && rear[crear - 1] == rquit) //We have finished with circulation through the front gears and rear gears. Exit.
			break;

		if (rear[crear - 1] == rquit) // We have circulated through all the rear gears. Circulate the front gears.
		{
			//Find the frontmost full gear. After this, increment the gear before that, and set all the following gears to increment by 1 after that.
			for (a = cfront - 1;/*We shouldn't reach 0, because we already checked for that before.*/;a--)
			{
				//Is the gear before this full? If not, then gear a is the frontmost full-gear.
				if (a == 0 || front[a] != front[a - 1] + 1)
				{
					//Increment the gear before this fullgear, and set the following gears to follow-up immediately (i.e., increment to 40, and the gears after into 41, 42, 43, and so on).
					front[a++]--;

					for (b = flg - cfront + a + 1;a < cfront;a++)
						front[a] = b++;

					break;
				}
			}

			//Reset all the rear gears.
			for (a = 0, b = rlg - crear + a + 1;a < crear;a++)
				rear[a] = b++;
		}
		else //Circulate the rear gearing. This is similar to circulating the front gearing.
		{
			for (a = crear - 1;;a--)
			{
				if (a == 0 || rear[a] != rear[a - 1] + 1)
				{
					rear[a++]--;

					for (b = rlg - crear + a + 1;a < crear;a++)
						rear[a] = b++;

					break;
				}
			}
		}
	}

	//Output the max_fronts and the max_rears.
	out << max_front[0];

	for (a = 1;a < cfront;a++)
		out << " " << max_front[a];

	out << "\n" << max_rear[0];

	for (a = 1;a < crear;a++)
		out << " " << max_rear[a];

	out << "\n";
	out.close ();

	if (DEBUG)
	{
		cout << clock ();
		cin.get ();
	}

	return 0;
}