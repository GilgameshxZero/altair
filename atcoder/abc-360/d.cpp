#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, y, z) for (LL x(y), c(z), d{x < c ? 1LL : -1LL}; x != c; x += d)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, T;
	cin >> N >> T;
	array<vector<LL>, 2> X;
	string S;
	cin >> S;
	RF(i, 0, N) {
		LL x;
		cin >> x;
		X['1' - S[i]].push_back(x);
	}
	sort(X[0].begin(), X[0].end());
	sort(X[1].begin(), X[1].end());

	array<LL, 3> P{0, 0, 0};
	LL Z{0};
	while (P[0] < X[0].size()) {
		while (P[1] < X[1].size() && X[1][P[1]] <= X[0][P[0]] + T + T) {
			P[1]++;
		}
		while (P[2] < X[1].size() && X[1][P[2]] <= X[0][P[0]]) {
			P[2]++;
		}
		Z += P[1] - P[2];
		P[0]++;
	}
	cout << Z << '\n';
	return 0;
}
