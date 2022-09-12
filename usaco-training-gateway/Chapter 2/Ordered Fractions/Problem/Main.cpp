/*
ID: yangchess1
LANG: C++
PROB: frac1
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

struct Frac
{
	int a, b;

	Frac (int x, int y)
	{
		a = x;
		b = y;
	}
};

bool Comp (Frac a, Frac b)
{
	if (((double)a.a / a.b) < ((double)b.a / b.b))
		return true;
	else if (((double)a.a / a.b) > ((double)b.a / b.b))
		return false;
	else
	{
		if (a.a < b.a)
			return true;
		else if (a.a > b.a)
			return false;
		else
			return (a.b < b.b);
	}
}

int main ()
{
	std::ifstream in ("frac1.in");
	std::ofstream out ("frac1.out");
	vector<Frac> f;
	int n;

	in >> n;

	for (int a = 1;a <= n;a++)
		for (int b = 0;b <= a;b++)
			f.push_back (Frac(b, a));

	sort (f.begin (), f.end (), Comp);
	out << f[0].a << "/" << f[0].b << "\n";

	for (int a = 1;a < f.size ();a++)
		if (((double)f[a].a / f[a].b) != ((double)f[a - 1].a / f[a - 1].b))
			out << f[a].a << "/" << f[a].b << "\n";

	out.close ();

	return 0;
}