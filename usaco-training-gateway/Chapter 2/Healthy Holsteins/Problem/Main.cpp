/*
ID: yangchess1
LANG: C++
PROB: holstein
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
#include <vector>

using namespace std;

//Number of set bits in x (pretty unsafe/slow but whatever).
int popcount (int x)
{
	int r = 0;

	for (int a = 0;a < 32;a++)
		if (x & (1 << a))
			r++;

	return r;
}

int main ()
{
	std::ifstream in ("holstein.in");
	std::ofstream out ("holstein.out");
	int V, G, req[25], feed[15][25], min_c = 16, min_n, temp[25];
	
	in >> V;
	for (int a = 0;a < V;a++)
		in >> req[a];

	in >> G;
	for (int a = 0;a < G;a++)
		for (int b = 0;b < V;b++)
			in >> feed[a][b];

	in.close ();

	//Test all combinations of feeds/brute force.
	for (int a = 0, b, c;a < 1 << G;a++)
	{
		if (min_c <= popcount (a))
			continue;

		memset (temp, 0, sizeof (temp));
		for (b = 0;b < G;b++)
			if (a & (1 << b))
				for (c = 0;c < V;c++)
					temp[c] += feed[b][c];

		//Does it work?
		for (b = 0;b < V;b++)
			if (temp[b] < req[b])
				break;

		if (b == V) //Works.
		{
			min_c = popcount (a);
			min_n = a;
		}
	}

	out << min_c << " ";
	int j, k;
	for (j = 0, k = 0;j < min_c - 1 && k < G;k++)
	{
		if (min_n & (1 << k))
		{
			out << k + 1 << " ";
			j++;
		}
	}

	for (;k < G;k++)
		if (min_n & (1 << k))
			out << k + 1 << "\n";

	out.close ();
	return 0;
}