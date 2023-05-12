/*
ID: yangchess1
LANG: C++
PROB: packrec
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

//A sloppy complete search.

int max (int a, int b, int c)
{
	return max (a, max (b, c));
}

int max (int a, int b, int c, int d)
{
	return max (max (a, b), max (c, d));
}

int min (int a, int b, int c, int d)
{
	return min (min (a, b), min (c, d));
}

struct R
{
	int w, l;

	R ()
	{
		w = l = 0;
	}

	R (int a, int b)
	{
		w = a;
		l = b;
	}
};

bool Comp (R a, R b)
{
	return (a.w < b.w);
}

R r[4];
vector<R> ans;
int area = 1000000;

void Verify (int w, int l)
{
	if (l * w < area)
	{
		ans.clear ();
		area = l * w;


		ans.push_back (R (min (l, w), max (l, w)));
	}
	else if (l * w == area)
		ans.push_back (R (min (l, w), max (l, w)));
}

int main ()
{
	std::ifstream in ("packrec.in");
	std::ofstream out ("packrec.out");
	int q[4];

	for (int a = 0;a < 4;a++)
		in >> r[a].w >> r[a].l;

	in.close ();

	q[0] = 0;
	q[1] = 1;
	q[2] = 2;
	q[3] = 3;

	//Permutations.
	for (int a = 0;a < 24;a++)
	{
		//Rotations.
		for (int b = 0;b < 2;b++)
		{
			for (int c = 0;c < 2;c++)
			{
				for (int d = 0;d < 2;d++)
				{
					for (int e = 0;e < 2;e++)
					{
						//Layouts.
						Verify (r[q[0]].w + r[q[1]].w + r[q[2]].w + r[q[3]].w, max (r[q[0]].l, r[q[1]].l, r[q[2]].l, r[q[3]].l));
						Verify (max (r[q[0]].w + r[q[1]].w + r[q[2]].w, r[q[3]].l), max (r[q[0]].l, r[q[1]].l, r[q[2]].l) + r[q[3]].w);
						Verify (max (r[q[0]].l + r[q[1]].l, r[q[2]].l) + r[q[3]].l, max (r[q[3]].w, r[q[2]].w + max (r[q[0]].w, r[q[1]].w)));
						Verify (r[q[0]].w + r[q[3]].w + max (r[q[1]].w, r[q[2]].w), max (r[q[0]].l, r[q[1]].l + r[q[2]].l, r[q[3]].l));

						if (r[q[2]].w >= r[q[1]].w + r[q[3]].w)
							Verify (max (r[q[0]].w + r[q[2]].w, r[q[1]].w + r[q[3]].w), max (r[q[0]].l, r[q[2]].l + r[q[1]].l, r[q[2]].l + r[q[3]].l));
						else if (r[q[2]].w >= r[q[3]].w)
							Verify (max (r[q[0]].w + r[q[2]].w, r[q[1]].w + r[q[3]].w), max (r[q[0]].l + r[q[1]].l, r[q[2]].l + r[q[1]].l, r[q[2]].l + r[q[3]].l));
						else if (r[q[3]].w <= r[q[2]].w + r[q[0]].w)
							Verify (max (r[q[0]].w + r[q[2]].w, r[q[1]].w + r[q[3]].w), max (r[q[0]].l + r[q[1]].l, r[q[3]].l + r[q[0]].l, r[q[2]].l + r[q[3]].l));
						else
							Verify (max (r[q[0]].w + r[q[2]].w, r[q[1]].w + r[q[3]].w), max (r[q[1]].l, r[q[3]].l + r[q[0]].l, r[q[2]].l + r[q[3]].l));

						swap (r[3].l, r[3].w);
					}

					swap (r[2].l, r[2].w);
				}

				swap (r[1].l, r[1].w);
			}

			swap (r[0].l, r[0].w);
		}
		
		next_permutation (q, q + 4);
	}

	out << area << "\n";

	sort (ans.begin (), ans.end (), Comp);

	out << ans[0].w << " " << ans[0].l << "\n";

	for (int a = 1;a < ans.size ();a++)
		if (ans[a].w != ans[a - 1].w)
			out << ans[a].w << " " << ans[a].l << "\n";

	out.close ();

	return 0;
}