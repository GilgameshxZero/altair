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
		LL N, A, Q;
		cin >> N >> A >> Q;
		string S;
		cin >> S;
		if (A == N) {
			cout << "YES\n";
			continue;
		}
		LL P{A};
		bool done{false};
		RF(i, 0, Q) {
			P += S[i] == '+';
			A += S[i] == '+';
			A -= S[i] == '-';
			if (A == N) {
				done = true;
				cout << "YES\n";
				break;
			}
		}
		if (!done) {
			if (P >= N) {
				cout << "MAYBE\n";
			} else {
				cout << "NO\n";
			}
		}
	}

	return 0;
}
