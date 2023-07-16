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

LL compute(LL A, LL B) {
	if (A == B) {
		return 2;
	}
	if (B > A) {
		if (A == 0) {
			return 0;
		}
		if (B >= 3 * A) {
			B = A + (B - A) % (2 * A);
		}
		LL nA{B}, nB{B - A};
		return (1 + compute(nA, nB)) % 3;
	} else {
		if (B == 0) {
			return 1;
		}
		if (A >= 3 * B) {
			A = B + (A - B) % (2 * B);
		}
		LL nA{B}, nB{A - B};
		return (1 + compute(nA, nB)) % 3;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		array<bool, 3> H;
		H.fill(false);
		RF(i, 0, N) {
			LL b;
			cin >> b;

			if (A[i] == 0 && b == 0) {
				;
			} else {
				H[compute(A[i], b)] = true;
			}
		}
		LL Z{0};
		RF(i, 0, 3) {
			Z += H[i];
		}
		cout << (Z <= 1 ? "YES" : "NO") << '\n';
	}

	return 0;
}
