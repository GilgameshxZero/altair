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

LL const MOD{1000000007};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, M;
	cin >> N >> M;

	vector<LL> V;
	RF(i, 0, 1 << N) {
		bool fail{false};
		RF(j, 0, N) {
			if (i & (1 << j)) {
				continue;
			}
			if (j + 1 == N) {
				fail = true;
				break;
			}
			if (i & (1 << (j + 1))) {
				fail = true;
				break;
			}
			j++;
		}
		if (!fail) {
			V.push_back(i);
		}
	}

	vector<LL> Z(1 << N), Y;
	Z[0] = 1;
	RF(i, 0, M) {
		Y.clear();
		Y.resize(1 << N, 0);
		RF(j, 0, 1 << N) {
			RF(k, 0, V.size()) {
				if ((V[k] & j) != j) {
					continue;
				}
				Y[V[k] ^ j] = (Y[V[k] ^ j] + Z[j]) % MOD;
			}
		}
		swap(Z, Y);
	}
	cout << Z[0];

	return 0;
}
