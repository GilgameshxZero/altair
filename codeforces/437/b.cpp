#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

int sum, limit, bits, t, x, y, ok, 
	add[2], sadd, split[200000], cs, ans[100000], ca;
double l;
bool lookup[100001];

int getbits (int x)
{
	for (int a = 0;a < 32;a++)
		if (x >> a == 0)
			return a;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> sum >> limit;
	bits = getbits (sum);
	ca = cs = 0;
	memset (lookup, 0, sizeof (lookup));

	for (int a = 0;a < bits;a++)
	{
		if (sum & (1 << a))
		{
			if ((1 << a) > limit)
				split[cs++] = 1 << a;
			else
			{
				lookup[1 << a] = true;
				ans[ca++] = 1 << a;
			}
		}
	}

	while (cs > 0)
	{
		t = split[--cs];
		x = t & -t;
		y = getbits (x) - 1;
		ok = 0;

		if (x == 1)
		{
			cout << "-1\n";
			return 0;
		}

		sadd = 0;

		for (int a = 0, b = x / 2;
			sadd < 2 || (b <= limit && ok < 2);
			a++, b += (1 << y))
		{
			if (b <= limit && lookup[b] == false && ok < 2)
			{
				lookup[b] = true;
				ans[ca++] = b;
				ok++;
			}
			else if (sadd < 2)
				add[sadd++] = b;
		}

		for (int a = ok;a < 2;a++)
			split[cs++] = add[a - ok];
	}

	printf ("%i\n", ca);
	for (int a = 0;a < ca - 1;a++)
		printf ("%i ", ans[a]);
	printf ("%i\n", ans[ca - 1]);

	return 0;
}