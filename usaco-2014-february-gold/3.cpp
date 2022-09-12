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

//Skip lists.

typedef pair<int, int> pii;

struct RNode
{
	int pos, time;
	RNode *next;

	RNode (int npos, int ntime, RNode *nnext)
	{
		pos = npos;
		time = ntime;
		next = nnext;
	}
};

const int MHEIGHT = 50, PROB = 50; //50/100 i.e. 50%
RNode *slist[MHEIGHT]; //Each slist[a] represents a level of the skip-list, like a linked list. NULL = tail node. Sort by `pos`.
int ccow, cres[2], seat[200000], load[200000];

void AddNode (int pos, int time)
{
	int level = 0;

	//See how high this node should make it.
	while ((rand () % 100 < PROB) && (level < MHEIGHT - 1))
		level++;

	//Find insertion point in all the heights.
	RNode *cur_node, *insert[MHEIGHT];

	cur_node = slist[MHEIGHT - 1];

	for (int a = MHEIGHT - 1;a >= 0;a--)
	{
		while (cur_node->next != NULL && cur_node->pos < pos)
		{
		}
	}
}

int main ()
{
	std::ifstream in ("boarding.in");
	std::ofstream out ("boarding.out");
	int *cres1, *cres2;

	srand (1);

	in >> ccow;

	for (int a = 0;a < ccow;a++)
		in >> seat[a] >> load[a];

	//Begin restriction enumeration.
	for (int a = 0;a < MHEIGHT;a++)
		slist[a] = new RNode (0, 0, NULL); //Head nodes.

	cres[(ccow - 1) % 2] = 2;
	cres[ccow % 2] = 0;

	res[(ccow - 1) % 2][0] = pii (0, 0);
	res[(ccow - 1) % 2][1] = pii (seat[ccow - 1], seat[ccow - 1] + load[ccow - 1]);

	int ans = 0;

	for (int a = ccow - 2, high, c, d;a >= 0;a--)
	{
		high = 0;
		c = (a + 1) % 2;
		d = a % 2;

		//Copy restrictions from cow ahead.
		for (int b = 0;b < cres[c];b++)
		{
			if (res[c][b].first <= seat[a])
			{
				res[d][cres[d]++] = pii (res[c][b].first - 1, res[c][b].second);

				if (res[d][cres[d] - 1].second - res[d][cres[d] - 1].first > high)
					high = res[d][cres[d] - 1].second - res[d][cres[d] - 1].first;
			}
			else
				res[d][cres[d]++] = pii (res[c][b].first, res[c][b].second);
		}

		res[d][cres[d]++] = pii (seat[a], seat[a] + load[a] + high);

		if (res[d][cres[d] - 1].second > ans)
			ans = res[d][cres[d] - 1].second;

		cres[c] = 0;
	}

	out << ans << "\n";
	out.close ();

	return 0;
}