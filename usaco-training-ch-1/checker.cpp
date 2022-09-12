/*
ID: yangchess1
LANG: C++
PROB: checker
*/

/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

Backup this program every so often in the Backup files in case something goes wrong later.

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
#include <sstream>
#include <vector>

using namespace std;

//Standard DFS.
int dim, level, cans, ans[100000][13], top[3];
bool diag[2][25], col[13];

bool Smaller (int x[13], int y[13])
{
	for (int a = 0;a < 13;a++)
	{
		if (x[a] < y[a])
			return true;
		else if (x[a] > y[a])
			return false;
	}

	return false;
}
 
void Solve ()
{
	if (level == dim)
	{
		for (int a = 0;a < 13;a++)
			ans[cans + 1][a] = ans[cans][a];

		//Check if the answer is one of the top 3.
		if (Smaller (ans[cans], ans[top[0]]))
		{
			top[2] = top[1];
			top[1] = top[0];
			top[0] = cans;
		}
		else if (Smaller (ans[cans], ans[top[1]]))
		{
			top[2] = top[1];
			top[1] = cans;
		}
		else if (Smaller (ans[cans], ans[top[2]]))
			top[2] = cans;

		cans++;
	}
	else
	{
		for (int a = 0;a < dim;a++)
		{
			if (col[a] == false && diag[0][dim - 1 - level + a] == false && diag[1][level + a - 1] == false)
			{
				col[a] = true;
				diag[0][dim - 1 - level + a] = true;
				diag[1][level + a - 1] = true;
				ans[cans][level] = a + 1;
				level++;
				Solve ();
				level--;
				col[a] = false;
				diag[0][dim - 1 - level + a] = false;
				diag[1][level + a - 1] = false;
			}
		}
	}
}

int main ()
{
	std::ifstream in ("checker.in");
	std::ofstream out ("checker.out");

	for (int a = 0;a < 25;a++)
		diag[0][a] = diag[1][a] = 0;
 
	for (int a = 0;a < 13;a++)
	{
		col[a] = 0;
		ans[99999][a] = 14;
	}
 
	in >> dim;
	top[0] = top[1] = top[2] = 99999;
	level = 0;
	Solve ();
 
	for (int a = 0;a < 3;a++)
	{
		for (int b = 0;b < dim - 1;b++)
			out << ans[top[a]][b] << " ";

		out << ans[top[a]][dim - 1] << "\n";
	}

	out << cans << "\n";
 
	return 0;
}