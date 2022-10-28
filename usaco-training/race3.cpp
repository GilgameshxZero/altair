/*
ID: yangchess1
LANG: C++
PROB: race3
*/

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

#define DEBUG 0
//#define DEBUG 1

struct Point
{
	int arrow[100], carrow;
};

//This is our floodfill function. It takes as input a set of points and their arrows, a starting location for the floodfill, and a point to avoid walking on. As output, it returns a set of points accessable from the starting point, and the number of points in the set. The last variable should always be 0 when calling from an outside source, as it specifies where in the input set to start saving points. It is used primarily while recursing. The output set is somewhat relatable to a 'visited' structure.
void IdentifySet (int *set, int *cset, Point *point, int start, int avoidance, int set_start)
{
	bool flag;

	//First we should setup cset and add the current 'start' point to the set.
	*cset = set_start;
	set[(*cset)++] = start;
	
	//Recurse on all outgoing arrows.
	for (int a = 0;a < point[start].carrow;a++)
	{
		//Make sure we don't have to avoid this point, if it is 'avoidance', or already in the set (already visited).
		if (point[start].arrow[a] != avoidance)
		{
			flag = false;

			//Scan the set for matching points; the set represents points already visited.
			for (int b = 0; b < set_start;b++)
			{
				if (point[start].arrow[a] == set[b])
				{
					flag = true;
					break;
				}
			}

			if (flag == false)
				IdentifySet (set, cset, point, point[start].arrow[a], avoidance, *cset); //We can pass cset (2nd variable) onto this function without data loss, as we know cset is an output variable.
		}
	}

	return;
}

int CompareInt (const void *var1, const void *var2)
{
	const int a = *reinterpret_cast<int *>(const_cast<void *>((var1))), b = *reinterpret_cast<int *>(const_cast<void *>((var2)));

	if (a > b)
		return 1;
	else if (a < b)
		return -1;

	return 0;
}

int main ()
{
	std::ifstream in ("race3.in");
	std::ofstream out ("race3.out");
	Point point[50];
	bool flag;
	int set[2][50], cset[2], unavoidable[50], splitting[50], cunavoid = 0, csplit = 0, cpoint = 0;

	for (int a = 0;a < 50;a++)
		point[a].carrow = 0;

	for (int a;;)
	{
		in >> a;

		if (a == -2)
			cpoint++;
		else if (a == -1)
			break;
		else //Some arrow has been specified.
			point[cpoint].arrow[point[cpoint].carrow++] = a;
	}

	in.close ();

	//We scan through every point. To test if it is unavoidable, we "remove" the point from the graph and floodfill starting from point 0 and see if we can still get to point N. Further, to test if the point is a splitting point, we perform a floodfill starting at that point and see if the set of accessable points overlaps with the previous set.
	for (int a = 1, b;a < cpoint - 1;a++)
	{
		IdentifySet (set[0], &cset[0], point, 0, a, 0);

		//See if the ending point is in the set.
		for (b = 0;b < cset[0];b++)
		{
			if (set[0][b] == cpoint - 1) //If the ending point can be accessed, then we move on to the next point to scan.
				break;
		}

		if (b < cset[0]) //The loop above finish prematurely.
			continue; //This sends the program to the beginning of the outer for loop.
		
		//As without this point, we cannot reach the end, it is unavoidable.
		unavoidable[cunavoid++] = a;

		//For this function call, we ignore the 'avoidance' variable, as it is not needed.
		IdentifySet (set[1], &cset[1], point, a, -1, 0);

		//Check if there are any overlapping points in our two sets. First sort the two sets.
		qsort (set[0], cset[0], sizeof (int), CompareInt);
		qsort (set[1], cset[1], sizeof (int), CompareInt);
		
		//As it is sorted, we can orderly scan through our sets and identify identical points. It's hard to explain, try to think about it.
		flag = false;
		for (int c = 0, d = 0;c < cset[0] && d < cset[1];)
		{
			if (set[0][c] < set[1][d])
			{
				c++; //lol
				continue;
			}
			else if (set[0][c] > set[1][d])
			{
				d++;
				continue;
			}
			else if (set[0][c] == set[1][d]) //Since we have overlapping points, it must mean that this point is not a splitting point.
			{
				flag = true;
				break;
			}
		}

		if (flag == false) //It's a splitting point.
			splitting[csplit++] = a;
	}

	out << cunavoid;

	for (int a = 0;a < cunavoid;a++)
		out << " " << unavoidable[a];

	out << "\n" << csplit;

	for (int a = 0;a < csplit;a++)
		out << " " << splitting[a];

	out << "\n";
	out.close ();

	return 0;
}