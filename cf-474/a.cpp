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

	string s = "qwertyuiopasdfghjkl;zxcvbnm,./", t;
	char c;
	int pos[128];
	cin >> c >> t;

	for (int a = 0;a < 128;a++)
		for (int b = 0;b < s.length ();b++)
			if (s[b] == a)
				pos[a] = b;

	for (int a = 0;a < t.length ();a++)
		cout << s[pos[t[a]] - 2 * (c == 'R') + 1];

	return 0;
}