#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		string S;
		char D;
		cin >> N >> D >> S;
		bool done{false};
		RF(i, 0, N) {
			if (S[i] < D) {
				done = true;
				cout << S.substr(0, i) << D << S.substr(i) << '\n';
				break;
			}
		}
		if (!done) {
			cout << S << D << '\n';
		}
	}

	return 0;
}
