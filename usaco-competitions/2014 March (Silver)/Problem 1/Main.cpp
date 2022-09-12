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

struct Node
{
	int x, y, dist;
	bool in_tree;
};

const int INF = numeric_limits<int>::max ();
int dmat[2000][2000]; //Distance matrix.

int main ()
{
	std::ifstream in ("irrigation.in");
	std::ofstream out ("irrigation.out");
	Node farms[2000];
	int n, c, cost = 0;
	
	in >> n >> c;

	for (int a = 0;a < n;a++)
		in >> farms[a].x >> farms[a].y;

	in.close ();

	//Initialize parameters.
	for (int a = 0;a < n;a++)
	{
		farms[a].in_tree = false;
		farms[a].dist = INF;

		for (int b = 0;b < n;b++)
		{
			dmat[a][b] = dmat[b][a] = (farms[a].x - farms[b].x) * (farms[a].x - farms[b].x) + (farms[a].y - farms[b].y) * (farms[a].y - farms[b].y);

			if (dmat[a][b] < c)
				dmat[a][b] = dmat[b][a] = INF;
		}
	}

	//Source node.
	farms[0].in_tree = true;
	farms[0].dist = 0;

	for (int a = 1;a < n;a++)
		farms[a].dist = dmat[0][a];

	//Prim.
	for (int a = 0, low, slow;a < n - 1;a++)
	{
		low = slow = INF;

		//Find closest node.
		for (int a = 0;a < n;a++)
		{
			if (farms[a].in_tree == false && farms[a].dist < low)
			{
				low = farms[a].dist;
				slow = a;
			}
		}

		//No closest node?
		if (slow == INF)
		{
			out << "-1\n";
			out.close ();

			return 0;
		}

		//Update params.
		farms[slow].in_tree = true;
		cost += low;

		//Relax edges.
		for (int a = 0;a < n;a++)
		{
			if (farms[a].in_tree == false && farms[a].dist > dmat[slow][a])
				farms[a].dist = dmat[slow][a];
		}
	}

	out << cost << "\n";
	out.close ();

	return 0;
}