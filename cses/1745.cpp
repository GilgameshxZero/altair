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

bitset<100001> Z;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	cin >> N;
	vector<LL> X(N);
	RF(i, 0, N) {
		cin >> X[i];
	}

	Z[0] = true;
	RF(i, 0, N) {
		RF(j, Z.size() - 1 - X[i], -1) {
			if (Z[j]) {
				Z[j + X[i]] = true;
			}
		}
	}
	vector<LL> Y;
	RF(i, 1, Z.size()) {
		if (Z[i]) {
			Y.push_back(i);
		}
	}
	cout << Y.size() << '\n';
	RF(i, 0, Y.size()) {
		cout << Y[i] << ' ';
	}

	return 0;
}
