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
		int cd[6];
		for (int a = 0;a < 5;a++)
			cin >> cd[a];

		if (cd[0] == 0)
			break;

		bool flag2 = false;
		for (int a = 1;a <= 52;a++)
		{
			bool flag = false;
			for (int b = 0;b < 5;b++)
				if (a == cd[b])
				{
					flag = true;
					break;
				}

			if (flag)
				continue;

			int cpy[6];
			memcpy (cpy, cd, sizeof (cd));

			sort (cpy, cpy + 3);
			cpy[5] = a;
			sort (cpy + 3, cpy + 6);

			int p1, p2, ans = 0;
			p1 = 2;
			p2 = 5;
			for (;p1 >= 0 && p2 >= 3;)
			{
				if (cpy[p1] > cpy[p2])
					ans++, p1--, p2--;
				else
					p2--;
			}

			if (ans <= 1)
			{
				cout << a << "\n";
				flag2 = true;
				break;
			}
		}

		if (!flag2)
			cout << "-1\n";
	}

	return 0;
}