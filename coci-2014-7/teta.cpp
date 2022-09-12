#include <iostream>
#include <cstdio>
using namespace std;

int main ()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int K, X, T, price[20], menu[4], order[20], orig, red, pr;

	memset (order, 0, sizeof (order));

	cin >> K;
	for (int a = 0;a < K;a++)
		cin >> price[a];
	cin >> X;
	red = X;
	for (int a = 0;a < 4;a++)
		cin >> menu[a],
		red -= price[--menu[a]];
	cin >> T;
	orig = 0;
	for (int a = 0, b;a < T;a++)
		cin >> b,
		order[--b]++,
		orig += price[b];

	pr = orig;

	if (red >= 0)
		cout << orig << "\n";
	else
	{
		while (order[menu[0]] >= 0 || order[menu[1]] >= 0 || order[menu[2]] >= 0 || order[menu[3]] >= 0)
		{
			int subpr = 0;
			for (int a = 0;a < 4;a++)
				if (order[menu[a]] > 0)
					subpr += price[menu[a]];
			if (X < subpr)
			{
				pr = pr + X - subpr;
				for (int a = 0;a < 4;a++)
					if (order[menu[a]] > 0)
						order[menu[a]]--;
			}
			else break;
		}
		cout << pr << "\n";
	}

	return 0;
}