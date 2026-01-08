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
int dp[35][505][505];

int main() {
	ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen("input0.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	//compute dp space
	for (int a = 33; a >= 0; a--) {
		for (int b = 0; b < 505; b++) {
			for (int c = 0; c < 505; c++) {
				for (int d = 0; d < 35; d++) {
					if (a * d <= b && d * (d - 1) / 2 <= c)
						dp[a][b][c] = max(dp[a][b][c], d + dp[a + 1][b - a * d][c - d * (d - 1) / 2]);
				}
				if (a == 0)
					dp[a][b][c]--;
			}
		}
	}

	int T;
	cin >> T;
	for (int a = 0; a < T; a++) {
		int R, B;
		cin >> R >> B;

		cout << "Case #" << a + 1 << ": " << dp[0][R][B] << "\n";
	}

	return 0;
}