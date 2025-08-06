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

array<array<LL, 22>, 1000001> B;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, Q;
	cin >> N >> Q;

	B[0][0] = 0;
	RF(i, 1, B.size()) {
		B[i][0] = -1;
	}
	RF(i, 0, N) {
		LL a, b;
		cin >> a >> b;
		B[b][0] = max(B[b][0], a);
	}
	RF(i, 1, B.size()) {
		B[i][0] = max(B[i][0], B[i - 1][0]);
	}
	RF(i, 1, B[0].size()) {
		RF(j, 0, B.size()) {
			B[j][i] = B[B[j][i - 1]][i - 1];
		}
	}
	RF(i, 0, Q) {
		LL a, b;
		cin >> a >> b;
		LL Z{0}, z;
		for (z = 0; z < B[0].size() && B[b][z] >= a; z++);
		z--;
		while (z >= 0) {
			Z += (1 << z);
			b = B[b][z];
			for (z = 0; z < B[0].size() && B[b][z] >= a; z++);
			z--;
		}
		cout << Z << '\n';
	}

	return 0;
}
