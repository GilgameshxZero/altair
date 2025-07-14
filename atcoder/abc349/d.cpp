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

	LL L, R;
	cin >> L >> R;
	vector<LL> Z;
	Z.push_back(L);
	while (L != R) {
		LL M{1};
		while (L % 2 == 0 && L * M + M * 2 <= R) {
			M *= 2;
			L /= 2;
		}
		L = L * M + M;
		Z.push_back(L);
	}
	cout << Z.size() - 1 << '\n';
	RF(i, 0, Z.size() - 1) {
		cout << Z[i] << ' ' << Z[i + 1] << '\n';
	}

	return 0;
}
