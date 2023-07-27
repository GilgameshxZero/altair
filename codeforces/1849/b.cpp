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
		map<LL, vector<LL>> G;
		RF(i, 0, N) {
			LL x;
			cin >> x;
			G[x % K].push_back(i);
		}
		vector<LL> Z;
		RF(i, 0, G[0].size()) {
			Z.push_back(G[0][i]);
		}
		for (auto i{G.rbegin()}; i != G.rend(); i++) {
			RF(j, 0, i->second.size()) {
				Z.push_back(i->second[j]);
			}
		}
		RF(i, 0, N) {
			cout << Z[i] + 1 << ' ';
		}
		cout << '\n';
	}

	return 0;
}
