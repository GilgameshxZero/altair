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
		LL N, K;
		cin >> N >> K;
		set<pair<LL, LL>> M;
		map<LL, LL> O;
		RF(i, 0, N) {
			LL x;
			cin >> x;
			O[x]++;
		}
		for (auto &i : O) {
			M.insert({i.second, i.first});
		}
		LL G{N}, R{0}, S(K), E(0), Y(0);
		auto P{M.begin()};
		while (S > 0) {
			S -= P->first;
			P++;
			E++;
		}
		LL Z{LLONG_MAX / 2};
		RF(i, 0, N + 1) {
			Z = min(Z, (LL)M.size() - E + i - Y);
			while (!O.empty() && O.begin()->first == i) {
				auto x{M.find({O.begin()->second, O.begin()->first})};
				if (P == M.end()) {
					M.erase(x);
					E = min(E, (LL)M.size());
				} else if (*x > *P) {
					M.erase(x);
				} else if (*x == *P) {
					P = M.erase(x);
				} else {
					S += x->first;
					while (P != M.end() && S > 0) {
						S -= P->first;
						P++;
						E++;
					}
					E--;
					M.erase(x);
				}
				O.erase(O.begin());
				Y++;
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
