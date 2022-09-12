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

struct Synonym
{
	string orig, repl;
	int crr;
};

const int HASHSIZE = 558083,
	HASHPRIME = 97;
int m, n, f_r, f_l;
string essay[100000], ts, ts2, dict[100000][2];
vector<Synonym> hdict[HASHSIZE];

void ToLower (string *s)
{
	for (int a = 0;a < s->length ();a++)
		if ((*s)[a] < 97)
			(*s)[a] += 32;
}

int CountR (string *s)
{
	int r = 0;
	for (int a = 0;a < s->length ();a++)
		if ((*s)[a] == 'R' || (*s)[a] == 'r')
			r++;
	return r;
}

int Hash (string *s)
{
	int r = 0;
	for (int a = 0;a < s->length ();a++)
		r = (r * HASHPRIME + (*s)[a]) % HASHSIZE;
	return r;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> m;
	for (int a = 0;a < m;a++)
	{
		cin >> essay[a];
		ToLower (&essay[a]);
	}

	cin >> n;
	for (int a = 0;a < n;a++)
	{
		cin >> dict[a][0] >> dict[a][1];
		ToLower (&dict[a][0]);
		ToLower (&dict[a][1]);
	}
	for (int k = 0;k < 2;k++)
	{
		for (int a = 0, b, c, d;a < n;a++)
		{
			ts = dict[a][0];
			ts2 = dict[a][1];

			b = Hash (&ts2);
			for (c = 0;c < hdict[b].size ();c++)
			{
				if (hdict[b][c].orig == ts2)
				{
					ts2 = hdict[b][c].repl;
					break;
				}
			}

			b = CountR (&ts2);
			c = CountR (&ts);
			if (b < c || (b == c && ts2.length () < ts.length ()))
			{
				c = Hash (&ts);
				for (d = 0;d < hdict[c].size ();d++)
				{
					if (hdict[c][d].orig == ts && (hdict[c][d].crr > b || (hdict[c][d].crr == b && hdict[c][d].repl.length () > ts2.length ())))
					{
						hdict[c][d].crr = b;
						hdict[c][d].repl = ts2;
						break;
					}
				}
				if (d == hdict[c].size ())
				{
					hdict[c].push_back (Synonym ());
					hdict[c][d].orig = ts;
					hdict[c][d].crr = b;
					hdict[c][d].repl = ts2;
				}
			}
		}
	}

	f_r = f_l = 0;
	for (int a = 0, b, c;a < m;a++)
	{
		b = Hash (&essay[a]);
		for (c = 0;c < hdict[b].size ();c++)
		{
			if (hdict[b][c].orig == essay[a])
			{
				f_r += hdict[b][c].crr;
				f_l += hdict[b][c].repl.length ();
				break;
			}
		}
		if (c == hdict[b].size ())
			f_r += CountR (&essay[a]),
			f_l += essay[a].length ();
	}

	cout << f_r << " " << f_l << "\n";

	return 0;
}