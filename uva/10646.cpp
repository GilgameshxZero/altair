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

	int cpd[128];
	for (int a = 0;a < 128;a++)
		cpd[a] = a - '0';
	cpd['A'] = cpd['T'] = cpd['J'] = cpd['Q'] = cpd['K'] = 10;

	int t;
	cin >> t;
	for (int a = 1; a <= t;a++)
	{
		string pile[52];
		for (int b = 0;b < 52;b++)
			cin >> pile[b];

		int y = 0, rem = 0;
		for (int b = 0;b < 3;b++)
		{
			int k = cpd[pile[26 - rem][0]];
			y+=k;
			rem += 1 + (10 - k);
		}

		cout << "Case " << a << ": ";
		if (y < 27 - rem)
			cout << pile[y];
		else
			cout << pile[26 + y - (27 - rem)];
		cout << "\n";
	}

	return 0;
}