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

	int x;
	string s;
	cin >> x >> s;

	bitset<26> ok;
	ok.reset ();
	for (int a = 0;a < x;a++)
	{
		if (s[a] < 'a')
			s[a] += 'a' - 'A';
		ok[s[a] - 'a'] = true;
	}

	for (int a = 0;a < 26;a++)
		if (ok[a] == false)
		{
			cout << "NO\n";
			return 0;
		}

	cout << "YES\n";

	return 0;
}