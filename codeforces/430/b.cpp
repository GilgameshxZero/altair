#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int main ()
{
	//freopen ("input.txt", "r", stdin);
	//freopen ("output.txt", "w", stdout);

	int n, k, x, max = 0, last;
	vector<int> balls, t;

	cin >> n >> k >> x;
	for (int a = 0, b;a < n;a++)
	{
		cin >> b;
		balls.push_back (b);
	}

	for (int a = 0, b, run, lc;a < n + 1;a++)
	{
		t = balls;
		t.insert (t.begin () + a, x);
		last = -1;

		//Test sequence.
		while (last != t.size ())
		{
			last = t.size ();

			//Process.
			for (b = 0, run = 0, lc = -1;b < t.size ();b++)
			{
				if (t[b] == lc)
					run++;
				else
				{
					if (run >= 3)
					{
						t.erase (t.begin () + b - run, t.begin () + b);
						b = -1;
						break;
					}

					lc = t[b];
					run = 1;
				}
			}

			if (b == t.size ())
				if (run >= 3)
					t.erase (t.begin () + b - run, t.begin () + b);
		}

		//Check.
		if (n - (int)t.size () > max)
			max = n - (int)t.size ();
	}

	cout << max << "\n";

	return 0;
}