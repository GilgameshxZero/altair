#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, f, t)                                      \
	for (LL x(f), _t(t), _d{x < _t ? 1LL : -1LL}; x != _t; \
			 x += _d)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		unordered_map<LL, unordered_map<LL, LL>> X[3];
		unordered_map<
			LL,
			unordered_map<LL, unordered_map<LL, LL>>>
			Y;
		LL Z{0};
		RF(i, 2, N) {
			Z += X[0][A[i - 2]][A[i - 1]] + X[1][A[i - 2]][A[i]] +
				X[2][A[i - 1]][A[i]] -
				3 * Y[A[i - 2]][A[i - 1]][A[i]];
			Y[A[i - 2]][A[i - 1]][A[i]]++;
			X[0][A[i - 2]][A[i - 1]]++;
			X[1][A[i - 2]][A[i]]++;
			X[2][A[i - 1]][A[i]]++;
		}
		cout << Z << '\n';
	}

	return 0;
}
