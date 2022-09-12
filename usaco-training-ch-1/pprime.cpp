/*
ID: yangchess1
LANG: C++
PROB: pprime
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

vector<int> GeneratePalindromes (int low, int high)
{
	vector<int> palin;
	int dlow = static_cast<int>(log10 (low)) + 1,
		dhigh = static_cast<int>(log10 (high)) + 1;

	for (int a = dlow, b, c, d, e, f, g, h, i, j;a <= dhigh;a++)
	{
		b = static_cast<int>(a / 2.0 + 0.5);
		c = max (low / static_cast<int>(pow (10, a / 2)), static_cast<int>(pow (10, b - 1)));
		d = min (high / static_cast<int>(pow (10, a / 2)), static_cast<int>(pow (10, b) - 1));

		for (e = c;e <= d;e++)
		{
			f = static_cast<int>(log10 (e)) + 1;

			for (g = h = 0, i = e;g < f;g++)
			{
				h += i % 10;
				i /= 10;
				h *= 10;
			}

			if (a % 2 == 0)
				j = e * static_cast<int>(pow (10, a / 2)) + h / 10;
			else
				j = (e - e % 10) * static_cast<int>(pow (10, a / 2)) + h / 10;

			if (j <= high)
				palin.push_back (j);
		}
	}

	return palin;
}

int main ()
{
	std::ifstream in ("pprime.in");
	std::ofstream out ("pprime.out");
	vector<int> palin;
	int primes[10000];
	int low, high, cprimes = 0;
	
	in >> low >> high;
	in.close ();

	//Generate all primes under 10000 (square root of 100000000, max).
	bool prime;

	for (int a = 2, b, c;a < 10000;a++)
	{
		c = static_cast<int>(sqrt (a));

		for (b = 0, prime = true;b < cprimes && primes[b] <= c;b++)
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

	//Create palindromes in low-high range in order and test whether they are prime.
	palin = GeneratePalindromes (low, high);

	for (int a = 0, b, c;a < palin.size ();a++)
	{
		c = static_cast<int>(sqrt (palin[a]));

		for (b = 0, prime = true;b < cprimes && primes[b] <= c;b++)
		{
			if (palin[a] % primes[b] == 0)
			{
				prime = false;
				break;
			}
		}

		if (prime == true)
			out << palin[a] << "\n";
	}

	out.close ();

	return 0;
}