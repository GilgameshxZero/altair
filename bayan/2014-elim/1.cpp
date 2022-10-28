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
	freopen ("in.txt", "r", stdin);
	freopen ("out.txt", "w", stdout);

	int t;
	cin >> t;
	for (int k = 0;k < t;k++)
	{
		int n;
		cin >> n;
		string temp;
		cin >> temp;
		int cnt[128];
		memset (cnt, 0, sizeof (cnt));
		for (int a = 0;a < n;a++)
			cnt[temp[a]]++;
		
		int winner[51];
		memset (winner, 0, sizeof (winner));
		for (int a = 0;a < n;a++)
		{
			if (temp[a] == 'R')
				winner[cnt['S']]++;
			if (temp[a] == 'S')
				winner[cnt['P']]++;
			if (temp[a] == 'P')
				winner[cnt['R']]++;
		}

		for (int b = 50;b >= 0;b--)
			if (winner[b] != 0)
			{
				cout << "Case #" << k + 1 << ":\n" << winner[b];
				if (k < t - 1)
					cout << "\n";
				break;
			}
	}

	return 0;
}