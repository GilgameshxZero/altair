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
		cin >> N;
		if (N == 0) {
			cout << "YES\n";
			continue;
		}
		string S;
		while (N > 0) {
			S += '0' + (N % 2);
			N /= 2;
		}
		RF(i, 0, S.length()) {
			if (S[i] == '1') {
				break;
			}
			S.push_back('0');
		}
		string SS{S};
		reverse(S.begin(), S.end());
		if (SS == S) {
			if (S.length() % 2 == 1) {
				cout << (S[S.length() / 2] == '0' ? "YES" : "NO") << '\n';
				continue;
			}
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}

	return 0;
}
