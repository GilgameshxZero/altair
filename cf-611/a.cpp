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
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	string s1, s2;
	int i;

	cin >> i >> s1 >> s2;

	int ans;
	if (s2 == "week")
	{
		ans = 52;
		if (i == 5 || i == 6)
			ans++;
	}
	else
	{
		ans = 12;
		if (i == 31)
			ans = 7;
		else if (i == 30)
			ans = 11;
	}

	cout << ans;

	return 0;
}