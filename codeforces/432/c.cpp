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

const int SEIVE = 316;
const int primes[65] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313};
int n, x[100001];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input2.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	vector<pair<int, int> > moves;

	cin >> n;
	for (int a = 1;a <= n;a++)
		cin >> x[a];

	for (int a = 1;a <= n;a++)
	{
		int diff = abs (x[a] - a) + 1, l = diff, s = x[a], g = a, t, p;

		while (diff != 1)
		{
			if (s < g)
				for (int b = 0;b < 65;b++)
				{
					t = abs (diff - primes[b]);
					if ((t >= 3 && t < l) || t == 1)
					{
						l = t;
						p = s + primes[b];
					}
				}
			else
				for (int b = 0;b < 65;b++)
				{
					t = abs (diff - primes[b]);
					if ((t >= 3 && t < l) || t == 1)
					{
						l = t;
						p = s - primes[b];
					}
				}

			moves.push_back (make_pair (min(s, p), max(s, p)));
			swap (x[s], x[p]);
			diff = l;
			s = p;

			if (l == 3)
			{
				moves.push_back (make_pair (min (s, g), max (s, g)));
				swap (x[s], x[g]);
				break;
			}
			else if (l == 1)
				break;
		}
	}

	cout << moves.size () << "\n";
	for (int a = 0;a < moves.size ();a++)
		cout << moves[a].first << " " << moves[a].second << "\n";

	return 0;
}