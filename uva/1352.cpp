#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

int n, perm[24][6], tshift[6] = {0, 3, 1, 4, 2, 5}, lshift[6] = {1, 5, 2, 3, 0, 4}, cube[4][6], rot[4], ans;
vector<string> hvec;

void Apply (int seq[6], int shift[6])
{
	int temp[6];

	for (int a = 0;a < 6;a++)
		temp[a] = seq[shift[a]];
	
	memcpy (seq, temp, 6 * sizeof (int));
}

void GenPerms ()
{
	int orig[6] = {0, 1, 2, 3, 4, 5}, temp[6];
	
	memcpy (temp, orig, 6 * sizeof (int));
	for (int a = 0;a < 4;a++)
	{
		memcpy (perm[a], temp, 6 *sizeof (int));
		Apply (temp, tshift);
	}

	memcpy (temp, orig, 6 * sizeof (int));
	Apply (temp, lshift);
	for (int a = 4;a < 8;a++)
	{
		memcpy (perm[a], temp, 6 *sizeof (int));
		Apply (temp, tshift);
	}

	memcpy (temp, orig, 6 * sizeof (int));
	Apply (temp, tshift);
	Apply (temp, lshift);
	Apply (temp, lshift);
	Apply (temp, lshift);
	for (int a = 8;a < 12;a++)
	{
		memcpy (perm[a], temp, 6 *sizeof (int));
		Apply (temp, tshift);
	}

	memcpy (temp, orig, 6 * sizeof (int));
	Apply (temp, tshift);
	Apply (temp, lshift);
	for (int a = 12;a < 16;a++)
	{
		memcpy (perm[a], temp, 6 *sizeof (int));
		Apply (temp, tshift);
	}

	memcpy (temp, orig, 6 * sizeof (int));
	Apply (temp, lshift);
	Apply (temp, lshift);
	Apply (temp, lshift);
	for (int a = 16;a < 20;a++)
	{
		memcpy (perm[a], temp, 6 *sizeof (int));
		Apply (temp, tshift);
	}

	memcpy (temp, orig, 6 * sizeof (int));
	Apply (temp, lshift);
	Apply (temp, lshift);
	for (int a = 20;a < 24;a++)
	{
		memcpy (perm[a], temp, 6 *sizeof (int));
		Apply (temp, tshift);
	}
}

void Solve (int lvl)
{
	if (lvl == n)
	{
		int temp[4][6], count[24], cost = 0;

		for (int a = 0;a < n;a++)
		{
			memcpy (temp[a], cube[a], 6 * sizeof (int));
			Apply (temp[a], perm[rot[a]]);
		}

		for (int a = 0;a < 6;a++)
		{
			memset (count, 0, 24 * sizeof (int));

			for (int b = 0;b < n;b++)
				count[temp[b][a]]++;

			int max = 0;

			for (int b = 0;b < 24;b++)
				if (count[b] > max)
					max = count[b];

			cost += n - max;
		}

		if (cost < ans)
			ans = cost;
	}
	else
	{
		for (int a = 0;a < 24;a++)
		{
			rot[lvl] = a;
			Solve (lvl + 1);
		}
	}
}

int main ()
{
	string tstr;

	//freopen ("Text.txt", "r", stdin);

	GenPerms ();
	rot[0] = 0;
	cin >> n;
		
	while (n != 0)
	{
		hvec.clear ();

		for (int a = 0;a < n;a++)
		{
			for (int b = 0, c;b < 6;b++)
			{
				cin >> tstr;

				for (c = 0;c < hvec.size ();c++)
				{
					if (hvec[c] == tstr)
					{
						cube[a][b] = c;
						break;
					}
				}

				if (c == hvec.size ())
				{
					hvec.push_back (tstr);
					cube[a][b] = c;
				}
			}
		}

		if (n == 1)
		{
			cout << "0\n";
			cin >> n;
			continue;
		}

		ans = 100000;
		Solve (1);
		
		cout << ans << "\n";
		cin >> n;
	}

	return 0;
}