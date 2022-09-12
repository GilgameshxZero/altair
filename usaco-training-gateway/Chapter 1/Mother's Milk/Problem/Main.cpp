/*
ID: yangchess1
LANG: C++
PROB: milk3
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
#include <stack>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Triple
{
	int a, b, c;
};

Triple MTriple (int a, int b, int c)
{
	Triple rtrn;

	rtrn.a = a;
	rtrn.b = b;
	rtrn.c = c;

	return rtrn;
}

string its (int a)
{
   stringstream ss;
   ss << a;
   return ss.str();
}

int main ()
{
	std::ifstream in ("milk3.in");
	std::ofstream out ("milk3.out");
	stack<Triple> s;
	Triple t;
	string ans;
	bool vis[21][21][21];
	int ma, mb, mc;
	int a, b, c;

	in >> ma >> mb >> mc;
	in.close ();

	for (a = 0;a < 21;a++)
		for (b = 0;b < 21;b++)
			for (c = 0;c < 21;c++)
				vis[a][b][c] = false;

	//Begin DP.
	s.push (MTriple (0, 0, mc));

	while (!s.empty ())
	{
		//Already been here.
		if (vis[s.top ().a][s.top ().b][s.top ().c] == true)
		{
			s.pop ();
			continue;
		}

		t.a = s.top ().a;
		t.b = s.top ().b;
		t.c = s.top ().c;
		s.pop ();

		vis[t.a][t.b][t.c] = true;

		//Try all possible ways to move milk (a->b, a->c, b->a, b->c, c->a, c->b).
		if (t.a + t.b > mb)
			s.push (MTriple (t.a + t.b - mb, mb, t.c));
		else
			s.push (MTriple (0, t.a + t.b, t.c));

		if (t.a + t.c > mc)
			s.push (MTriple (t.a + t.c - mc, t.b, mc));
		else
			s.push (MTriple (0, t.b, t.a + t.c));

		if (t.b + t.a > ma)
			s.push (MTriple (ma, t.b + t.a - ma, t.c));
		else
			s.push (MTriple (t.b + t.a, 0, t.c));

		if (t.b + t.c > mc)
			s.push (MTriple (t.a, t.b + t.c - mc, mc));
		else
			s.push (MTriple (t.a, 0, t.b + t.c));

		if (t.c + t.a > ma)
			s.push (MTriple (ma, t.b, t.c + t.a - ma));
		else
			s.push (MTriple (t.c + t.a, t.b, 0));

		if (t.c + t.b > mb)
			s.push (MTriple (t.a, mb, t.c + t.b - mb));
		else
			s.push (MTriple (t.a, t.c + t.b, 0));
	}

	for (int a = 0;a <= mc;a++)
		if (vis[0][mc - a][a] == true)
			ans += its (a) + " ";

	out << ans.substr (0, ans.length () - 1) << "\n";
	out.close ();

	return 0;
}