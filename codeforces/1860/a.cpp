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
		string S;
		cin >> S;
		bool alt{true};
		RF(i, 1, S.length()) {
			alt &= S[i] != S[i - 1];
		}
		if (!alt) {
			cout << "YES\n";
			RF(i, 0, S.length()) {
				cout << "()";
			}
			cout << '\n';
		} else {
			if (S.length() >= 3) {
				cout << "YES\n";
				RF(i, 0, S.length()) {
					cout << "(";
				}
				RF(i, 0, S.length()) {
					cout << ")";
				}
				cout << '\n';
			} else if (S == "()") {
				cout << "NO\n";
			} else {
				cout << "YES\n(())\n";
			}
		}
	}

	return 0;
}
