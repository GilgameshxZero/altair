/*
ID: yangchess1
LANG: C++
PROB: sprime
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
#include <queue>

using namespace std;

int main ()
{
	std::ifstream in ("sprime.in");
	std::ofstream out ("sprime.out");
	queue<int> ans;
	int dig, cprimes = 0, primes[10000];

	in >> dig;
	in.close ();

	//Generate all primes under 10000.
	bool prime;

	for (int a = 2, b;a < 10000;a++)
	{
		for (b = 0, prime = true;b < cprimes;b++)
		{
			if (a % primes[b] == 0)
			{
				prime = false;
				break;
			}
		}

		if (prime == true)
			primes[cprimes++] = a;
	}

	//Generate superprimes.
	ans.push (2);
	ans.push (3);
	ans.push (5);
	ans.push (7);

	for (int a = 1, b = 4, c, d, e, f, g;a < dig;a++)
	{
		for (g = 0;b > 0;b--)
		{
			c = ans.front () * 10 + 1;
			ans.pop ();

			//Test whether c + some odd number is prime.
			for (d = 0;d < 5;c += 2)
			{
				d++;
				f = static_cast<int>(sqrt (c));

				for (e = 0, prime = true;e < cprimes && primes[e] <= f;e++)
				{
					if (c % primes[e] == 0)
					{
						prime = false;
						break;
					}
				}

				if (prime == true)
				{
					ans.push (c);
					g++;
				}
			}
		}

		b = g;
	}

	while (!ans.empty ())
	{
		out << ans.front () << "\n";
		ans.pop ();
	}

	out.close ();

	return 0;
}