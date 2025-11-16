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

LL const MOD{998244353};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		unordered_map<LL, LL> M;
		RF(i, 0, N) {
			LL x;
			cin >> x;
			M[x]++;
		}
		vector<pair<LL, LL>> F;
		for (auto &i : M) {
			F.push_back({i.second, i.first});
		}
		sort(F.begin(), F.end());
		LL Z{1};
		RF(i, 0, F.size()) {
			Z = Z * (F[i].first + 1) % MOD;
		}
		vector<LL> Y(F.back().first);
		Y[0] = 1;
		RF(i, 0, F.size() - 1) {
			RF(j, Y.size() - 1 - F[i].first, -1) {
				Y[j + F[i].first] =
					(Y[j + F[i].first] + Y[j] * F[i].first) % MOD;
			}
		}
		RF(i, 0, Y.size()) {
			Z = (Z + MOD - Y[i]) % MOD;
		}
		cout << Z << '\n';
	}

	return 0;
}
