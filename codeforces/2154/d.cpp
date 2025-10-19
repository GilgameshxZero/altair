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

void cP(vector<unordered_set<LL>> &E, vector<bool> &P, LL x, LL p) {
	for (auto &i : E[x]) {
		if (i == p) {
			continue;
		}
		P[i] = !P[x];
		cP(E, P, i, x);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<unordered_set<LL>> E(N);
		RF(i, 0, N - 1) {
			LL u, v;
			cin >> u >> v;
			E[u - 1].insert(v - 1);
			E[v - 1].insert(u - 1);
		}
		vector<bool> P(N);
		cP(E, P, N - 1, -1);
		vector<pair<LL, LL>> Z;
		queue<LL> Q;
		RF(i, 0, N) {
			if (E[i].size() == 1) {
				Q.push(i);
			}
		}
		bool pP{P[0]};
		RF(i, 0, N) {
			LL j{Q.front()};
			Q.pop();
			if (j == N - 1) {
				continue;
			}
			if (pP == P[j]) {
				Z.push_back({1, -1});
				pP = !pP;
			}
			Z.push_back({2, j});
			for(auto &k : E[j]) {
				E[k].erase(j);
				if (E[k].size() == 1) {
					Q.push(k);
				}
			}
			Z.push_back({1, -1});
			pP = !pP;
		}
		cout << Z.size() << '\n';
		RF(i, 0, Z.size()) {
			if (Z[i].first == 1) {
				cout << "1\n";
			} else {
				cout << "2 " << Z[i].second + 1 << '\n';
			}
		}
		cout << '\n';
	}

	return 0;
}
