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
	string base, test;
	int ans = 0;
	for (int a = 0;a < s.length ();a++)
	{
		if (s[a] == '0')
			test += s[a];
		else
		{
			if (base.length () > test.length () || (base.length () == test.length () && base >= test))
				ans++;
			else
				ans = 1;
			base += test;
			test = s[a];
		}
	}
	if (base.length () > test.length () || (base.length () == test.length () && base >= test))
		ans++;
	else
		ans = 1;
	cout << ans << "\n";

	return 0;
}