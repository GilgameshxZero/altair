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
		string S, T;
		cin >> S >> T;
		set<LL> P[3];
		RF(i, 0, N) {
			P[S[i] - 'a'].insert(i);
		}
		bool fail{false};
		RF(i, 0, N) {
			RF(j, 0, 3) {
				P[j].erase(i);
			}
			if (S[i] == T[i]) {
				continue;
			}
			if (
				S[i] == 'a' && T[i] == 'b' && !P[1].empty() &&
				(P[2].empty() || *P[1].begin() < *P[2].begin())) {
				swap(S[i], S[*P[1].begin()]);
				P[0].insert(*P[1].begin());
				P[1].erase(P[1].begin());
			} else if (
				S[i] == 'b' && T[i] == 'c' && !P[2].empty() &&
				(P[0].empty() || *P[2].begin() < *P[0].begin())) {
				swap(S[i], S[*P[2].begin()]);
				P[1].insert(*P[2].begin());
				P[2].erase(P[2].begin());
			} else {
				fail = true;
				break;
			}
		}
		cout << (fail ? "NO" : "YES") << '\n';
	}

	return 0;
}
