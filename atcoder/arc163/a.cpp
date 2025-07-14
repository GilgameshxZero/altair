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

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		string S;
		cin >> N >> S;
		bool fail{true};
		RF(i, 1, N) {
			if (S[i] > S[0]) {
				cout << "Yes\n";
				fail = false;
				break;
			} else if (S[i] == S[0]) {
				if (S.substr(0, i) < S.substr(i)) {
					cout << "Yes\n";
					fail = false;
					break;
				}
			}
		}
		if (fail) {
			cout << "No\n";
		}
	}

	return 0;
}
