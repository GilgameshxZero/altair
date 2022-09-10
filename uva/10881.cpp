#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdio.h>

using namespace std;

struct Ant
{
	int pos, index, order;
	char dir;
};

Ant ant[10000];
int io[10000];

bool CompOrder (Ant a, Ant b)
{
	return a.pos < b.pos;
}

bool CompIndex (Ant a, Ant b)
{
	return a.index < b.index;
}

int main ()
{
	int ccase, l, t, n;

	//freopen ("Input.txt", "r", stdin);
	scanf ("%i", &ccase);

	for (int a = 0;a < ccase;a++)
	{
		scanf ("%i%i%i", &l, &t, &n);
		
		for (int b = 0;b < n;b++)
		{
			scanf ("%i %c", &ant[b].pos, &ant[b].dir);
			ant[b].index = b;
		}

		sort (ant, ant + n, CompOrder);

		for (int b = 0;b < n;b++)
			ant[b].order = b;

		sort (ant, ant + n, CompIndex);

		for (int b = 0;b < n;b++)
			io[b] = ant[b].order;

		for (int b = 0;b < n;b++)
			if (ant[b].dir == 'R')
				ant[b].pos += t;
			else
				ant[b].pos -= t;

		sort (ant, ant + n, CompOrder);
		printf ("Case #%i:\n", a + 1);

		for (int b = 0;b < n;b++)
		{
			if (ant[io[b]].pos < 0 || ant[io[b]].pos > l)
				printf ("Fell off\n");
			else
			{
				printf ("%i ", ant[io[b]].pos);

				if (io[b] > 0 && ant[io[b] - 1].pos == ant[io[b]].pos)
					printf ("Turning\n");
				else if (io[b] < n - 1 && ant[io[b] + 1].pos == ant[io[b]].pos)
					printf ("Turning\n");
				else
					printf ("%c\n", ant[io[b]].dir);
			}
		}

		printf ("\n");
	}

	return 0;
}