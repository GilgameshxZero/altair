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

	int n, m;
	cin >> n >> m;

	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	
	vector<int> b(m);
	for (int i = 0; i < m; ++i) {
		cin >> b[i];
	}

	int aeven=0, aodd=0, beven=0, bodd = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i] % 2 == 0) {
			++aeven;
		} else {
			aodd++;
		}
	}

	for (int i = 0; i < m; ++i) {
		if (b[i] % 2 == 0) {
			beven++;
		} else {
			bodd++;
		}
	}

	cout << min(aeven, bodd) + min(aodd, beven);
	return 0;
}
