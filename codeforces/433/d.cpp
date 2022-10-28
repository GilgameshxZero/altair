#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
const int MAXN = 1002;
int row, col, q, 
	board[MAXN][MAXN], u[MAXN][MAXN], d[MAXN][MAXN], l[MAXN][MAXN], r[MAXN][MAXN], 
	parL[MAXN], parR[MAXN];
pair<int, int> temp[MAXN];

int FindLPar (int i)
{
	if (parL[i] == i) return i;
	return parL[i] = FindLPar (parL[i]);
}

int FindRPar (int i)
{
	if (parR[i] == i) return i;
	return parR[i] = FindRPar (parR[i]);
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> row >> col >> q;
	parL[0] = parR[0] = 0;
	for (int a = 1;a <= row;a++)
		for (int b = 1;b <= col;b++)
			cin >> board[a][b];

	memset (u, 0, sizeof (u));
	memset (d, 0, sizeof (d));
	memset (l, 0, sizeof (l));
	memset (r, 0, sizeof (r));

	for (int a = 1;a <= col;a++)
	{
		for (int b = 1;b <= row;b++)
			u[b][a] = board[b][a] * (u[b - 1][a] + 1);
		for (int b = row;b > 0;b--)
			d[b][a] = board[b][a] * (d[b + 1][a] + 1);
	}
	for (int a = 1;a <= row;a++)
	{
		for (int b = 1;b <= col;b++)
			l[a][b] = board[a][b] * (l[a][b - 1] + 1);
		for (int b = col;b > 0;b--)
			r[a][b] = board[a][b] * (r[a][b + 1] + 1);
	}

	for (int a = 0, b, x, y, z;a < q;a++)
	{
		cin >> b >> x >> y;

		if (b == 1)
		{
			board[x][y] ^= 1;
			
			for (int e = 1;e <= row;e++)
				u[e][y] = board[e][y] * (u[e - 1][y] + 1);
			for (int e = row;e > 0;e--)
				d[e][y] = board[e][y] * (d[e + 1][y] + 1);
			for (int e = 1;e <= col;e++)
				l[x][e] = board[x][e] * (l[x][e - 1] + 1);
			for (int e = col;e > 0;e--)
				r[x][e] = board[x][e] * (r[x][e + 1] + 1);
		}
		else
		{
			z = 0;
			parL[col + 1] = parR[col + 1] = col + 1;

			for (int e = 1;e <= col;e++)
				parL[e] = parR[e] = e,
				temp[e].first = u[x][e],
				temp[e].second = e;
			sort (temp + 1, temp + col + 1);

			for (int e = col;e > 0;e--)
			{
				parR[temp[e].second] = temp[e].second + 1,
				parL[temp[e].second] = temp[e].second - 1;
				if (FindLPar (temp[e].second) < y && y < FindRPar (temp[e].second))
					z = max (z, temp[e].first * (FindRPar (temp[e].second) - FindLPar (temp[e].second) - 1));
			}

			for (int e = 1;e <= col;e++)
				parL[e] = parR[e] = e,
				temp[e].first = d[x][e],
				temp[e].second = e;
			sort (temp + 1, temp + col + 1);

			for (int e = col;e > 0;e--)
			{
				parR[temp[e].second] = temp[e].second + 1,
				parL[temp[e].second] = temp[e].second - 1;
				if (FindLPar (temp[e].second) < y && y < FindRPar (temp[e].second))
					z = max (z, temp[e].first * (FindRPar (temp[e].second) - FindLPar (temp[e].second) - 1));
			}

			parL[row + 1] = parR[row + 1] = row + 1;
			for (int e = 1;e <= row;e++)
				parL[e] = parR[e] = e,
				temp[e].first = l[e][y],
				temp[e].second = e;
			sort (temp + 1, temp + row + 1);

			for (int e = row;e > 0;e--)
			{
				parR[temp[e].second] = temp[e].second + 1,
				parL[temp[e].second] = temp[e].second - 1;
				if (FindLPar (temp[e].second) < x && x < FindRPar (temp[e].second))
					z = max (z, temp[e].first * (FindRPar (temp[e].second) - FindLPar (temp[e].second) - 1));
			}

			for (int e = 1;e <= row;e++)
				parL[e] = parR[e] = e,
				temp[e].first = r[e][y],
				temp[e].second = e;
			sort (temp + 1, temp + row + 1);

			for (int e = row;e > 0;e--)
			{
				parR[temp[e].second] = temp[e].second + 1,
				parL[temp[e].second] = temp[e].second - 1;
				if (FindLPar (temp[e].second) < x && x < FindRPar (temp[e].second))
					z = max (z, temp[e].first * (FindRPar (temp[e].second) - FindLPar (temp[e].second) - 1));
			}

			cout << z << "\n";
		}
	}

	return 0;
}