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
		set<LL> A;
		RF(i, 1, N + 1) {
			A.insert(i);
		}
		map<LL, LL> Y;
		vector<vector<LL>> Z;
		RF(i, N / 2, 0) {
			if (Y.count(i * 2)) {
				Z[Y[i * 2]].push_back(i);
				Y[i] = Y[i * 2];
				Y.erase(i * 2);
				A.erase(i);
			} else {
				Y[i] = Z.size();
				Z.push_back({});
				Z.back().push_back(i * 2);
				Z.back().push_back(i);
				A.erase(i * 2);
				A.erase(i);
			}
		}
		for (auto &i : A) {
			cout << i << ' ';
		}
		for (auto &i : Z) {
			for (auto &j : i) {
				cout << j << ' ';
			}
		}
		cout << '\n';
	}

	return 0;
}
