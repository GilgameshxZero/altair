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
	freopen("a.0.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif

	int T;
	cin >> T;

	while (T--) {
		int N;
		cin >> N;

		int big = 0, cBig = 0, tmp;
		for (int a = 0; a < N; a++) {
			cin >> tmp;
			if (tmp > big) {
				big = tmp;
				cBig = 1;
			} else if (tmp == big) {
				cBig++;
			}
		}

		if (cBig == 1) {
			cout << "1\n";
		} else if (cBig == N) {
			cout << N << "\n";
		} else {
			cout << "1\n";
		}
	}

	return 0;
}
