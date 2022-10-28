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
	string str;
	int a, b, c, d, ans = 0;
	cin >> a >> b >> c >> d;
	cin >> str;

	for (int x = 0;x < str.length ();x++)
	{
		if (str[x] == '1')
			ans += a;
		if (str[x] == '2')
			ans += b;
		if (str[x] == '3')
			ans += c;
		if (str[x] == '4')
			ans += d;
	}

	cout << ans;

	return 0;
}