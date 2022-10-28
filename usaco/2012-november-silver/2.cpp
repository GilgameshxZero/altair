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

long long dist[900][900];

int conv (int a, int b, int n)
{
	return a * n + b;
}

int main ()
{
	std::ifstream in ("distant.in");
	std::ofstream out ("distant.out");
	char grid[30][30];
	int n, a, b, large = 0;

	in >> n >> a >> b;
	in.get ();

	for (int x = 0;x < n;x++)
	{
		for (int y = 0;y < n;y++)
			grid[x][y] = in.get ();

		in.get ();
	}

	in.close ();

	for (int x = 0;x < 900;x++)
	{
		for (int y = 0;y < 900;y++)
		{
			if (x != y)
				dist[x][y] = 10000000000;
			else
				dist[x][y] = 0;
		}
	}

	for (int x = 0;x < n;x++)
	{
		for (int y = 0;y < n;y++)
		{
			if (x > 0)
			{
				if (grid[x - 1][y] != grid[x][y])
					dist[conv (x - 1, y, n)][conv (x, y, n)] = b;
				else
					dist[conv (x - 1, y, n)][conv (x, y, n)] = a;
			}
			if (y > 0)
			{
				if (grid[x][y - 1] != grid[x][y])
					dist[conv (x, y - 1, n)][conv (x, y, n)] = b;
				else
					dist[conv (x, y - 1, n)][conv (x, y, n)] = a;
			}
			if (x < n - 1)
			{
				if (grid[x + 1][y] != grid[x][y])
					dist[conv (x + 1, y, n)][conv (x, y, n)] = b;
				else
					dist[conv (x + 1, y, n)][conv (x, y, n)] = a;
			}
			if (y < n - 1)
			{
				if (grid[x][y + 1] != grid[x][y])
					dist[conv (x, y + 1, n)][conv (x, y, n)] = b;
				else
					dist[conv (x, y + 1, n)][conv (x, y, n)] = a;
			}
		}
	}

	//Floyd-Warshall.
	for (int k = 0;k < n * n;k++)
	{
		for (int i = 0;i < n * n;i++)
		{
			for (int j = 0;j < n * n;j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

	for (int x = 0;x < n * n;x++)
	{
		for (int y = 0;y < n * n;y++)
		{
			if (dist[x][y] > large && dist[x][y] != 10000000000)
				large = dist[x][y];
		}
	}

	out << large << "\n";
	out.close ();

	return 0;
}