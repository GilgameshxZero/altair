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
#include <functional>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

struct Cow
{
	int x, y;
	char type;

	bool operator< (const Cow &other) const
	{
		if (x == other.x)
		{
			if (type == 'G')
			{
				if (other.type == 'G')
					return false;
				return true;
			}
			return false;
		}
		return x < other.x;
	}
};

Cow cow[500];
int yco[500], ext[501], ign[500], cyc;
vector<int> fenwick;

//adds k to the element at pos x
void FenAdd (vector<int>& fen, int k, int x)
{
	for (;x < fen.size ();x += (x & -x))
		fen[x] += k;
}

//sums all elements before and including x
int FenSum (vector<int>& fen, int x)
{
	int r = 0;
	for (;x > 0;x -= (x & -x))
		r += fen[x];
	return r;
}

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("cowrect.in", "r", stdin);
	std::freopen ("cowrect.out", "w", stdout);

	int N;
	cin >> N;

	fenwick.resize (1002); //fensum (a) sums all 'h's before or equal to (a - 1)

	for (int a = 0;a < N;a++)
	{
		cin >> cow[a].x >> cow[a].y >> cow[a].type;
		if (cow[a].type == 'H')
		{
			yco[cyc] = cow[a].y;
			cyc++;
			FenAdd (fenwick, 1, cow[a].y + 1);
		}
	}

	sort (cow, cow + N);
	sort (yco, yco + cyc);

	//choose y bounds
	int maxhol = 1, minarea = 0;
	for (int a = 0;a < cyc;a++)
	{
		if (a > 0 && yco[a] == yco[a - 1])
			continue;
		for (int b = a;b < cyc;b++)
		{
			if (b > a && yco[b] == yco[b - 1])
				continue;
			if (FenSum (fenwick, yco[b] + 1) - FenSum (fenwick, yco[a]) < maxhol)
				continue;
			//dp answer for these bounds
			ign[N] = ext[N] = 0;
			for (int c = N - 1;c >= 0;c--)
			{
				if (cow[c].y < yco[a] || cow[c].y > yco[b])
				{
					if (ext[c + 1] == 0)
					{
						ext[c] = 0;
						ign[c] = 0;
					}
					else
					{
						ext[c] = ext[c + 1] + 1;
						ign[c] = ign[c + 1] + 1;
					}
					continue;
				}
				if (cow[c].type == 'G')
					ext[c] = 0,
					ign[c] = 0;
				else
				{
					ext[c] = ext[c + 1] + 1;
					ign[c] = ign[c + 1];
				}
				while (c != 0 && cow[c - 1].x == cow[c].x)
				{
					c--;
					if (cow[c].y < yco[a] || cow[c].y > yco[b])
					{
						if (ext[c + 1] == 0)
						{
							ext[c] = 0;
							ign[c] = 0;
						}
						else
						{
							ext[c] = ext[c + 1] + 1;
							ign[c] = ign[c + 1] + 1;
						}
						continue;
					}
					if (cow[c].type == 'G')
						ext[c] = 0,
						ign[c] = 0;
					else
					{
						ext[c] = ext[c + 1] + 1;
						ign[c] = ign[c + 1];
					}
				}
				if (ext[c] - ign[c] > maxhol)
					maxhol = ext[c] - ign[c],
					minarea = (yco[b] - yco[a]) * (cow[c + ext[c] - 1].x - cow[c].x);
				else if (ext[c] - ign[c] == maxhol)
					minarea = min (minarea, (yco[b] - yco[a]) * (cow[c + ext[c] - 1].x - cow[c].x));
			}
		}
	}

	cout << maxhol << "\n" << minarea << "\n";

	return 0;
}