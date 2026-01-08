#if defined(__GNUC__) && !defined(__clang__) && !defined(__MINGW32__)
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
		vector<unordered_set<LL>> EO(N), EI(N);
		RF(i, 0, M) {
			LL U, V;
			cin >> U >> V;
			U--;
			V--;
			EO[U].insert(V);
			EI[V].insert(U);
		}
		vector<LL> C(N);
		RF(i, 0, N) {
			C[i] = EO[i].size() / 2;
		}
		vector<bool> V(N, false);
		V[N - 1] = true;
		queue<LL> Q;
		Q.push(N - 1);
		bool fail{false};
		vector<pair<LL, LL>> Z;
		while (!Q.empty()) {
			LL I{Q.front()};
			Q.pop();
			if (I == 0) {
				fail = true;
				break;
			}
			for (auto &i : EI[I]) {
				if (V[i]) {
					continue;
				}
				if (C[i] == 0) {
					V[i] = true;
					Q.push(i);
				} else {
					Z.push_back({i, I});
					C[i]--;
				}
			}
		}
		if (fail) {
			cout << "-1\n";
		} else {
			cout << Z.size() << '\n';
			RF(i, 0, Z.size()) {
				cout << Z[i].first + 1 << ' ' << Z[i].second + 1 << '\n';
			}
		}
	}

	return 0;
}
