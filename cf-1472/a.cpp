#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
	ios_base::sync_with_stdio(false);

#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif

	int t;
	cin >> t;
	while (t-- > 0) {
		ll w, h, n;
		cin >> w >> h >> n;

		ll x = w * h;
		while (x % 2 == 0) {
			x /= 2;
			n = (n / 2) + ((n % 2 == 1) ? 1 : 0);
		}
		cout << ((n == 1) ? "YES" : "NO") << "\n";
	}

	return 0;
}
