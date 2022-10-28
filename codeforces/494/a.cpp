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

	string s;
	cin >> s;

	int cnt = 0, cans = 0, lastc = 0;
	for (int a = 0;a < s.length ();a++)
	{
		if (s[a] == '(')
			cnt++;
		else if (s[a] == ')')
		{
			cnt--;
			if (cnt < 0)
			{
				cout << "-1\n";
				return 0;
			}
		}
		else if (s[a] == '#')
		{
			cnt--;
			cans++;
			lastc = cnt;
			if (cnt < 0)
			{
				cout << "-1\n";
				return 0;
			}
		}
		lastc = min (lastc, cnt);
	}

	if (lastc - cnt < 0)
		cout << "-1\n";
	else
	{
		for (int a = 0;a < cans - 1;a++)
			cout << "1\n";
		cout << 1 + cnt << "\n";
	}

	return 0;
}