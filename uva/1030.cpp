#include <iostream>
using namespace std;

int n = 1, change, total;
char cube[10][10][10], view[6][10][10];

char *Get (int view, int x, int y, int z)
{
	if (view == 0)
		return &cube[z][y][x];
	if (view == 1)
		return &cube[n - 1 - y][z][x];
	if (view == 2)
		return &cube[n - 1 - z][n - 1 - y][x];
	if (view == 3)
		return &cube[y][n - 1 - z][x];
	if (view == 4)
		return &cube[n - 1 - x][y][z];
	if (view == 5)
		return &cube[x][y][n - 1 - z];
}

int main ()
{
	//freopen ("Text.txt", "r", stdin);
	cin >> n;

	while (n != 0)
	{
		for (int a = 0;a < 10;a++)
			for (int b = 0;b < 10;b++)
				for (int c = 0;c < 10;c++)
					cube[a][b][c] = '#';

		total = 0;
		cin.get ();

		for (int a = 0;a < n;a++)
		{
			for (int b = 0;b < 6;b++)
			{
				for (int c = 0;c < n;c++)
					view[b][a][c] = cin.get ();

				cin.get ();
			}
		}

		//Apply '.'
		for (int a = 0;a < 6;a++)
		{
			for (int b = 0;b < n;b++)
			{
				for (int c = 0;c < n;c++)
				{
					if (view[a][b][c] == '.')
					{
						for (int d = 0;d < n;d++)
						{
							if (*Get (a, b, c, d) != '.')
							{
								*Get (a, b, c, d) = '.';
								total++;
							}
						}
					}
				}
			}
		}

		//Continuously apply views on cube until nothing changes.
		do
		{
			change = 0;

			for (int a = 0;a < 6;a++)
			{
				for (int b = 0;b < n;b++)
				{
					for (int c = 0;c < n;c++)
					{
						if (view[a][b][c] != '.')
						{
							for (int d = 0;d < n;d++)
							{
								if (*Get (a, b, c, d) == '.')
									continue;
								if (*Get (a, b, c, d) == '#')
								{
									*Get (a, b, c, d) = view[a][b][c];
									break;
								}
								if (*Get (a, b, c, d) == view[a][b][c])
									break;

								change++;
								*Get (a, b, c, d) = '.';
							}
						}
					}
				}
			}

			total += change;
		} while (change != 0);

		cout << "Maximum weight: " << n * n * n - total << " gram(s)\n";
		cin >> n;
	}
}