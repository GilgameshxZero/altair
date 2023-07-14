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

void compute(vector<vector<LL>> &E, vector<LL> &C, LL &Z, LL x, LL p) {
	LL cc(E[x].size() - (p != -1));
	C[x] = 0;
	RF(i, 0, E[x].size()) {
		if (E[x][i] == p) {
			continue;
		}
		compute(E, C, Z, E[x][i], x);
		C[x] += C[E[x][i]] > 0;
	}
	if (C[x] < cc - 1) {
		Z += cc - 1 - C[x];
		C[x] = cc - 1;
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
		vector<vector<LL>> E(N);
		RF(i, 0, N - 1) {
			LL u, v;
			cin >> u >> v;
			u--;
			v--;
			E[u].push_back(v);
			E[v].push_back(u);
		}

		if (N == 1) {
			cout << "0\n";
			continue;
		}

		vector<LL> C(N);
		LL Z{0};
		RF(i, 0, N) {
			if (E[i].size() == 1) {
				compute(E, C, Z, i, -1);
				break;
			}
		}
		if (Z == 0) {
			cout << "1\n";
			continue;
		}

		Z = 0;
		RF(i, 0, N) {
			if (E[i].size() > 2) {
				compute(E, C, Z, i, -1);
				break;
			}
		}
		// RF(i, 0, N) {
		// 	cout << C[i] << ' ';
		// }
		// cout << '\n';
		cout << Z << '\n';
	}

	return 0;
}
