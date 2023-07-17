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
		unordered_map<LL, vector<LL>> S;
		RF(i, 0, N) {
			LL x;
			cin >> x;
			S[x].push_back(i);
		}
		bool fail{false};
		for (auto &i : S) {
			if (i.second.size() == 1) {
				fail = true;
				break;
			}
		}
		if (fail) {
			cout << -1 << '\n';
			continue;
		}
		vector<LL> Z(N);
		for (auto &i : S) {
			RF(j, 0, i.second.size()) {
				Z[i.second[j]] = i.second[(j + 1) % i.second.size()] + 1;
			}
		}
		RF(i, 0, N) {
			cout << Z[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
