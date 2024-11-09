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
		LL N, M;
		cin >> N >> M;
		vector<set<LL>> E(N);
		RF(i, 0, M) {
			LL U, V;
			cin >> U >> V;
			E[U - 1].insert(V - 1);
			E[V - 1].insert(U - 1);
		}
		priority_queue<pair<LL, LL>> PQ;
		RF(i, 0, N) {
			PQ.push({E[i].size(), i});
		}
		vector<pair<LL, pair<LL, LL>>> Z;
		while (PQ.top().first > 1) {
			LL i{PQ.top().second}, j{PQ.top().first};
			PQ.pop();
			if (E[i].size() != j) {
				continue;
			}
			Z.push_back({i, {*E[i].begin(), *next(E[i].begin())}});
			E[i].erase(Z.back().second.first);
			E[i].erase(Z.back().second.second);
			E[Z.back().second.first].erase(i);
			E[Z.back().second.second].erase(i);
			if (E[Z.back().second.first].count(Z.back().second.second)) {
				E[Z.back().second.first].erase(Z.back().second.second);
				E[Z.back().second.second].erase(Z.back().second.first);
			} else {
				E[Z.back().second.first].insert(Z.back().second.second);
				E[Z.back().second.second].insert(Z.back().second.first);
			}
			PQ.push({E[i].size(), i});
			PQ.push({E[Z.back().second.first].size(), Z.back().second.first});
			PQ.push({E[Z.back().second.second].size(), Z.back().second.second});
		}

		if (PQ.top().first != 0) {
			vector<LL> S;
			vector<pair<LL, LL>> P;
			RF(i, 0, N) {
				if (E[i].empty()) {
					S.push_back(i);
				} else if (i < *E[i].begin()) {
					P.push_back({i, *E[i].begin()});
				}
			}

			LL R{P.back().first}, X{P.back().second};
			P.pop_back();
			RF(i, 0, P.size()) {
				Z.push_back({R, {P[i].first, P[i].second}});
			}
			RF(i, 0, S.size()) {
				Z.push_back({S[i], {R, X}});
				X = S[i];
			}
		}

		cout << Z.size() << '\n';
		RF(i, 0, Z.size()) {
			cout << Z[i].first + 1 << ' ' << Z[i].second.first + 1 << ' '
					 << Z[i].second.second + 1 << '\n';
		}
	}

	return 0;
}
