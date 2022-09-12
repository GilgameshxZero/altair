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

	long long x[3][3];
	for (int a = 0;a < 3;a++)
		for (int b = 0;b < 3;b++)
			cin >> x[a][b];

	if ((x[0][1] > x[1][2] && x[0][2] >= x[1][1]) || 
		(x[0][1] > x[1][2] && x[1][1] > x[0][2] && (long long)ceil ((double)x[1][0] / (x[0][1] - x[1][2])) < (long long)ceil ((double)x[0][0] / (x[1][1] - x[0][2]))))
	{
		cout << "0\n";
		return 0;
	}

	long long ans = 1e15;
	for (int a = 0;a * x[2][1] < ans;a++)
	{
		if (x[0][1] + a <= x[1][2])
			continue;

		long long turns = ceil ((double)x[1][0] / (x[0][1] + a - x[1][2])); //turns to win, we must survive more than turns
		if (x[1][1] <= x[0][2])
			ans = min (ans, a * x[2][1]);
		for (int b = 0;b + x[0][2] <= x[1][1];b++) //loop through all def values
		{
			if (b + x[0][2] == x[1][1]) //same def as enemy atk
				ans = min (ans, a * x[2][1] + b * x[2][2]);
			else //calc how many hp we need to buy to suvive more than turns
			{
				long long buy = turns * (x[1][1] - b - x[0][2]) - x[0][0] + 1;
				if (buy < 0)
					buy = 0;
				ans = min (ans, a * x[2][1] + b * x[2][2] + buy * x[2][0]);
			}
		}
	}

	cout << ans;

	return 0;
}