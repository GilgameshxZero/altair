#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;

const int MAXN = 100;

int main ()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int t, n, ans, num[MAXN][MAXN], sum, least;
	string list[MAXN], base;
	cin >> t;

	for (int a, b, c, x = 0;x < t;x++)
	{
		cin >> n;
		for (a = 0;a < n;a++)
			cin >> list[a];

		//Reduce the first string.
		base = "";
		base += list[0][0];
		for (a = 1;a < list[0].length ();a++)
			if (list[0][a] != list[0][a - 1])
				base += list[0][a];

		//Loop through all the strings and find sum for each base char.
		memset (num, 0, MAXN * MAXN * sizeof (int));
		for (a = 0;a < n;a++)
		{
			for (b = 0, c = 0;b < list[a].length () && c < base.length ();)
			{
				if (list[a][b] == base[c])
				{
					for (;b < list[a].length () && c < base.length () && list[a][b] == base[c];b++)
						num[a][c]++;

					c++;
				}
				else
					break;
			}

			if (b != list[a].length () || c != base.length ())
				break;
		}

		//No answer.
		if (a != n)
		{
			cout << "Case #" << x + 1 << ": Fegla Won\n";
			continue;
		}

		//Search through all possible lengths of base letter.
		ans = 0;

		for (a = 0;a < base.length ();a++)
		{
			least = MAXN * MAXN;

			for (b = 1;b <= MAXN;b++)
			{
				sum = 0;
				for (c = 0;c < n;c++)
					sum += abs (b - num[c][a]);

				if (sum < least)
					least = sum;
			}

			ans += least;
		}

		cout << "Case #" << x + 1 << ": " << ans << "\n";
	}

	return 0;
}