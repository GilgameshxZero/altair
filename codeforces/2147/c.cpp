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
		if (N == 1) {
			cout << "YES\n";
			continue;
		}

		string X;
		X += S[0];
		X += S[1];
		RF(i, 2, N) {
			if (X[X.size() - 2] == X.back() && X.back() == S[i]) {
				continue;
			}
			X += S[i];
		}

		vector<string> Y;
		Y.push_back({X[0]});
		RF(i, 1, X.size()) {
			if (X[i] == X[i - 1]) {
				Y.push_back({X[i]});
			} else {
				Y.back() += X[i];
			}
		}

		bool fail{false};
		RF(i, 0, Y.size()) {
			if (Y[i][0] == '1' && Y[i].back() == '1' && (Y[i].size() / 2) % 2 == 1) {
				fail = true;
				break;
			}
		}

		cout << (fail ? "NO" : "YES") << '\n';

		// RF(i, 0, Y.size()) {
		// 	cout << Y[i] << ' ';
		// }
		// cout << '\n';
	}

	return 0;
}
