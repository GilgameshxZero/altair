#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, C[2];
		cin >> N >> C[0] >> C[1];
		string S;
		cin >> S;
		vector<LL> X(N);
		RF(i, 0, N) {
			cin >> X[i];
		}
		LL R[4]{};
		RF(i, 0, N) {
			R[S[i] - '0'] += X[i] / 2 + 1;
			R[2] += X[i] - X[i] / 2 - 1;
			R[3] += X[i] % 2 == 0;
		}
		if (
			R[0] > C[0] || R[1] > C[1] ||
			R[0] + R[1] + R[2] > C[0] + C[1]) {
			cout << "NO\n";
			continue;
		}
		if (
			R[0] == 0 && C[0] - R[2] - R[3] - (C[1] - R[1]) > 0 ||
			R[1] == 0 && C[1] - R[2] - R[3] - (C[0] - R[0]) > 0) {
			cout << "NO\n";
			continue;
		}
		cout << "YES\n";
	}

	return 0;
}
