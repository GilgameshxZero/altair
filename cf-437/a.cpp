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
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	string ch[4];
	bool cute[4];
	int c = 0;
	memset (cute, 0, sizeof (cute));
	for (int a = 0;a < 4;a++)
	{
		cin.get ();
		cin.get ();
		cin >> ch[a];
		cin.get ();
	}

	for (int a = 0;a < 4;a++)
	{
		bool flag = true;
		for (int b = 0;b < 4;b++)
		{
			if (a != b)
			{
				if (ch[a].length () * 2 > ch[b].length ())
					flag = false;
			}
		}

		if (flag == false)
		{
			flag = true;
			for (int b = 0;b < 4;b++)
			{
				if (a != b)
				{
					if (ch[a].length () < ch[b].length () * 2)
						flag = false;
				}
			}
		}
		cute[a] = flag;
		if (flag)
			c++;
	}

	if (c != 1)
		cout << "C\n";
	else
		for (int a = 0;a < 4;a++)
			if (cute[a])
				cout << (char)('A' + a) << "\n";

	return 0;
}