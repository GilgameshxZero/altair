#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.in", "r", stdin);
	freopen ("output.out", "w", stdout);
#endif

	while (true)
	{
		int n;
		cin >> n;

		if (n == 0)
			break;

		int y, z;
		y = z = 0;
		for (int a = 1;a < n;a++)
		{
			string tmp;
			cin >> tmp;

			if (tmp == "+y")
			{
				if (z == 0)
					y++;
			}
			if (tmp == "-y")
			{
				if (z == 0)
					y--;
			}
			if (tmp == "+z")
			{
				if (y == 2)
					z = 2, y = 0;
				if (y == 0)
					z++;
			}
			if (tmp == "-z")
			{
				if (y == 2)
					z = 2, y = 0;
				if (y == 0)
					z--;
			}

			y = (y % 4 + 4) % 4;
			z = (z % 4 + 4) % 4;

			if (z == 2)
				z = 0, y = 2;
			if (z == 1 || z == 3)
				y = 0;
		}

		if (z == 1)
			cout << "+z";
		else if (z == 3)
			cout << "-z";
		else if (y == 0)
			cout << "+x";
		else if (y == 1)
			cout << "+y";
		else if (y == 2)
			cout << "-x";
		else if (y == 3)
			cout << "-y";

		cout << '\n';
	}

	return 0;
}