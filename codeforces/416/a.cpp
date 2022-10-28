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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n, bot = -2e9, top = 2e9;
	string temp;
	char c;

	cin >> n;

	for (int a = 0, b;a < n;a++)
	{
		cin >> temp >> b >> c;

		if (temp == ">")
			if (c == 'Y')
				bot = max (bot, b + 1);
			else
				top = min (top, b);
		else if (temp == "<")
			if (c == 'Y')
				top = min (top, b - 1);
			else
				bot = max (bot, b);
		else if (temp == "<=")
			if (c == 'Y')
				top = min (top, b);
			else
				bot = max (bot, b + 1);
		else if (temp == ">=")
			if (c == 'Y')
				bot = max (bot, b);
			else
				top = min (top, b - 1);
	}

	if (bot <= top)
		cout << bot << "\n";
	else
		cout << "Impossible\n";

	return 0;
}