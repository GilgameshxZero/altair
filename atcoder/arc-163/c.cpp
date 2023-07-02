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

	unordered_set<LL> S;
	RF(i, 1, 40) {
		S.insert(i * (i + 1));
	}

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		if (N == 1) {
			cout << "Yes\n1\n";
			continue;
		}
		if (N == 2) {
			cout << "No\n";
			continue;
		}
		cout << "Yes\n";

		if (S.count(N)) {
			RF(i, 1, N - 3) {
				cout << i * (i + 1) << ' ';
			}
			cout << N - 2 << ' ';
			LL X{(N - 3) * (N - 2)};
			cout << 2 * X << ' ' << 3 * X << ' ' << 6 * X << '\n';
		} else {
			RF(i, 1, N) {
				cout << i * (i + 1) << ' ';
			}
			cout << N << '\n';
		}
	}

	return 0;
}
