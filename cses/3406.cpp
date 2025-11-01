#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	array<LL, 1424210> P;
	RF(i, 0, P.size()) {
		P[i] = i * (i + 1) / 2;
	}

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		auto it{lower_bound(P.begin(), P.end(), N)};
		if (it != P.end() && *it == N) {
			cout << 1 << '\n';
			continue;
		}
		bool fail{true};
		for (LL i{0}, j(it - P.begin()); i <= j; i++) {
			while (j >= i && (j == P.size() || P[i] + P[j] > N)) {
				j--;
			}
			if (P[i] + P[j] == N) {
				cout << "2\n";
				fail = false;
				break;
			}
		}
		if (fail) {
			cout << "3\n";
		}
	}

	return 0;
}
