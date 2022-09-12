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

	//sliding window
	string s;
	cin >> s;
	int x, y;
	cin >> x >> y;

	vector<int> mod_y; //10^k mod y
	mod_y.resize (s.length () + 1);
	mod_y[0] = 1;
	for (int a = 1;a < mod_y.size ();a++)
		mod_y[a] = (10 * mod_y[a - 1]) % y;

	int run[2]; //running mods, x, and y
	run[0] = run[1] = 0;
	for (int a = 0;a < s.length ();a++)
		run[1] = ((10 * run[1]) + s[a] - '0') % y;

	for (int a = 1;a < s.length ();a++)
	{
		//transform running mods
		run[0] = ((10 * run[0]) + s[a - 1] - '0') % x;
		run[1] = (run[1] - (s[a - 1] - '0') * mod_y[s.length () - a] + y) % y;

		if (s[a] == '0')
			continue;

		if (run[0] == 0 && run[1] == 0)
		{
			cout << "YES\n" << s.substr (0, a) << "\n" << s.substr (a, s.length () - a) << "\n";
			return 0;
		}
	}

	cout << "NO";

	return 0;
}