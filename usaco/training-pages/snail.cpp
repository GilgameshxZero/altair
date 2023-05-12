/*
ID: yangchess1
LANG: C++
PROB: snail
*/

/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

Backup this program every so often in the Backup files in case something goes wrong later.

Max's and mins: numeric_limits<type_name>::min().
*/

//Make the outer border all barriers, ease calculations.
#define MAX_LEN		122

const int EMPTY		= 0;
const int BARRIER	= 1 << 0;

//Visited while facing a certain direction.
const int UPVIS		= 1 << 1;
const int RIGHTVIS	= 1 << 2;
const int DOWNVIS	= 1 << 3;
const int LEFTVIS	= 1 << 4;

const int VISITED	= UPVIS | RIGHTVIS | DOWNVIS | LEFTVIS;

#define UP			0
#define RIGHT		1
#define DOWN		2
#define LEFT		3

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

int dim;

//Max squares from a certain point, not counting that point.
int MaxDistance (int map[MAX_LEN][MAX_LEN], int row, int col, int dir)
{
	int temp[2];

	if (dir == UP && ((map[row][col] & UPVIS) == 0))
	{
		for (int a = row - 1;a >= 0;a--)
		{
			if ((map[a][col] & BARRIER) == BARRIER)
			{
				for (int b = row;b > a;b--)
					map[b][col] |= UPVIS;

				temp[0] = row - a - 1 + MaxDistance (map, a + 1, col, RIGHT);
				temp[1] = row - a - 1 + MaxDistance (map, a + 1, col, LEFT);
				
				for (int b = row;b > a;b--)
					map[b][col] &= ~UPVIS;

				if (temp[0] > temp[1])
					return temp[0];
				else
					return temp[1];
			}
			else if ((map[a][col] & VISITED) != 0)
				return row - a;
		}
	}
	if (dir == RIGHT && ((map[row][col] & RIGHTVIS) == 0))
	{
		for (int a = col + 1;a < dim + 2;a++)
		{
			if ((map[row][a] & BARRIER) == BARRIER)
			{
				for (int b = col;b < a;b++)
					map[row][b] |= RIGHTVIS;

				temp[0] = a - 1 - col + MaxDistance (map, row, a - 1, UP);
				temp[1] = a - 1 - col + MaxDistance (map, row, a - 1, DOWN);
				
				for (int b = col;b < a;b++)
					map[row][b] &= ~RIGHTVIS;

				if (temp[0] > temp[1])
					return temp[0];
				else
					return temp[1];
			}
			else if ((map[row][a] & VISITED) != 0)
				return a - col;
		}
	}
	if (dir == DOWN && ((map[row][col] & DOWNVIS) == 0))
	{
		for (int a = row + 1;a < dim + 2;a++)
		{
			if ((map[a][col] & BARRIER) == BARRIER)
			{
				for (int b = row;b < a;b++)
					map[b][col] |= DOWNVIS;

				temp[0] = a - 1 - row + MaxDistance (map, a - 1, col, RIGHT);
				temp[1] = a - 1 - row + MaxDistance (map, a - 1, col, LEFT);
				
				for (int b = row;b < a;b++)
					map[b][col] &= ~DOWNVIS;

				if (temp[0] > temp[1])
					return temp[0];
				else
					return temp[1];
			}
			else if ((map[a][col] & VISITED) != 0)
				return a - row;
		}
	}
	if (dir == LEFT && ((map[row][col] & LEFTVIS) == 0))
	{
		for (int a = col - 1;a >= 0;a--)
		{
			if ((map[row][a] & BARRIER) == BARRIER)
			{
				for (int b = col;b > a;b--)
					map[row][b] |= LEFTVIS;

				temp[0] = col - a - 1 + MaxDistance (map, row, a + 1, UP);
				temp[1] = col - a - 1 + MaxDistance (map, row, a + 1, DOWN);
				
				for (int b = col;b > a;b--)
					map[row][b] &= ~LEFTVIS;

				if (temp[0] > temp[1])
					return temp[0];
				else
					return temp[1];
			}
			else if ((map[row][a] & VISITED) != 0)
				return col - a;
		}
	}

	return 0;
}

int main ()
{
	std::ifstream in ("snail.in");
	std::ofstream out ("snail.out");
	int nbarrier, map[MAX_LEN][MAX_LEN], itemp, itemp2; //Row, then column.
	char ctemp;

	in >> dim >> nbarrier;
	in.get ();

	//Treat border as barriers.
	for (int a = 0;a <= dim + 1;a++)
		for (int b = 0;b <= dim + 1;b++)
			map[a][b] = BARRIER;

	for (int a = 1;a <= dim;a++)
		for (int b = 1;b <= dim;b++)
			map[a][b] = EMPTY;

	for (int a = 0;a < nbarrier;a++)
	{
		ctemp = in.get ();
		in >> itemp;
		in.get ();
		map[itemp][ctemp - 64] = BARRIER;
	}

	for (int a = 0;a < dim + 2;a++)
	{
		for (int b = 0;b < dim + 2;b++)
		{
			if (map[a][b] == EMPTY)
				cout << ".";
			else if (map[a][b] == BARRIER)
				cout << "#";
		}

		cout << "\n";
	}

	in.close ();

	itemp = MaxDistance (map, 1, 1, RIGHT);
	itemp2 = MaxDistance (map, 1, 1, DOWN);

	if (itemp > itemp2)
		out << itemp << "\n";
	else
		out << itemp2 << "\n";

	out.close ();

	return 0;
}