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

	LL N, Q, Z;
	cin >> N >> Q;
	Z = N;
	vector<unordered_set<LL>> E(N);
	RF(i, 0, Q) {
		LL T, U, V;
		cin >> T;
		if (T == 1) {
			cin >> U >> V;
			Z -= E[U - 1].empty();
			Z -= E[V - 1].empty();
			E[U - 1].insert(V - 1);
			E[V - 1].insert(U - 1);
		} else {
			cin >> V;
			for (auto &j : E[V - 1]) {
				E[j].erase(V - 1);
				Z += E[j].empty();
			}
			Z += !E[V - 1].empty();
			E[V - 1].clear();
		}
		cout << Z << '\n';
	}

	return 0;
}
