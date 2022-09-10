#include <limits>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

int ccase, n, ans;
bool grid[17][17], tgrid[17][17];
vector<int> zeropos;

void Solve (int level, int pass)
{
	if (level == zeropos.size ())
	{
		int tans = pass, sum;
		memcpy (&tgrid, &grid, 17 * 17 * sizeof (bool));

		for (int a = 1;a < n;a++)
		{
			for (int b = 1;b <= n;b++)
			{
				sum = tgrid[a - 1][b] + tgrid[a][b - 1] + tgrid[a + 1][b] + tgrid[a][b + 1];

				if (sum == 1 || sum == 3)
				{
					if (tgrid[a + 1][b] == 0)
					{
						tans++;
						tgrid[a + 1][b] = 1;
					}
					else
						return;
				}
			}
		}

		for (int a = 1;a <= n;a++)
		{
			sum = tgrid[n - 1][a] + tgrid[n][a - 1] + tgrid[n + 1][a] + tgrid[n][a + 1];

			if (sum == 1 || sum == 3)
				return;
		}

		if (tans < ans)
			ans = tans;
	}
	else
	{
		Solve (level + 1, pass);
		grid[1][zeropos[level]] = true;
		Solve (level + 1, pass + 1);
		grid[1][zeropos[level]] = false;
	}
}

int main ()
{
	//freopen ("Text.txt", "r", stdin);

	cin >> ccase;
	for (int a = 0;a < ccase;a++)
	{
		zeropos.clear ();
		memset (&grid, 0, 17 * 17 * sizeof (bool));
		cin >> n;

		for (int b = 1;b <= n;b++)
		{
			for (int c = 1;c <= n;c++)
			{
				char p;
				cin >> p;
				grid[b][c] = p - '0';

				if (b == 1 && grid[b][c] == false)
					zeropos.push_back (c);
			}
		}

		ans = numeric_limits<int>::max ();
		Solve (0, 0);
		if (ans != numeric_limits<int>::max ())
			cout << "Case " << a + 1 << ": " << ans << "\n";
		else
			cout << "Case " << a + 1 << ": -1\n";
	}

	return 0;
}