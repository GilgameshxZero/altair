#include <iostream>

using namespace std;

//Brute force.
int t, r, c, m;
bool field[5][5];

void Solve (int lvl)
{
	if (lvl == 0)
	{
		//Test all locations.

	}
}

void main ()
{
	cin >> t;

	for (int a = 0;a < t;a++)
	{
		for (int b = 0;b < 5;b++)
			for (int c = 0;c < 5;c++)
				field[b][c] = false;

		cin >> r >> c >> m;
		Solve (m);
	}
}