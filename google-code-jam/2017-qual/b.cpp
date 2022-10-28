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

	int T;
	cin >> T;

	for (int K = 1;K <= T;K++) {
		string s;
		cin >> s;

		vector<string> mt (s.size ());
		mt.back () = s.back ();
		for (int a = s.size () - 2;a >= 0;a--) {
			if (s[a] > mt[a + 1][0])
				mt[a] = string (1, s[a] - 1) + string (mt[a + 1].size (), '9');
			else
				mt[a] = s[a] + mt[a + 1];
		}

		string ans = mt[0];
		while (ans[0] == '0')
			ans = ans.substr (1, ans.size () - 1);
		cout << "Case #" << K << ": " << ans << "\n";
	}

	return 0;
}