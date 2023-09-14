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

	LL x;

	LL T;
	cin >> T;
	while (T--) {
		LL N, K;
		cin >> N >> K;
		LL A{N - K};
		if (A == 0) {
			cout << "? " << 1 << endl;
			cin >> x;
			cout << "! " << x << endl;
			continue;
		}
		LL P1{K - 2 * A};
		if (P1 <= 0) {
			LL P{N % K}, A{(K - P) / 2};
			LL Z{0};
			RF(i, 0, N / K) {
				cout << "? " << i * K + 1 << endl;
				cin >> x;
				Z ^= x;
			}
			if (P == 0) {
				cout << "! " << Z << endl;
				continue;
			}
			cout << "? " << (N / K - 1) * K + 1 << endl;
			cin >> x;
			cout << "? " << N - K + 1 << endl;
			cin >> x;
			Z ^= x;
			cout << "? " << N - K - A + 1 << endl;
			cin >> x;
			Z ^= x;
			cout << "? " << N - K + 1 << endl;
			cin >> x;
			Z ^= x;

			cout << "! " << Z << endl;
		} else {
			LL P2{N - P1}, A1{(K - P1) / 2}, A2{(K - P2) / 2};
			while (A2 < 0) {
				P1 += 2;
				P2 -= 2;
				A1 = (K - P1) / 2;
				A2 = (K - P2) / 2;
			}
			LL Z{0};

			cout << "? " << 1 << endl;
			cin >> x;
			Z ^= x;
			cout << "? " << A1 + 1 << endl;
			cin >> x;
			Z ^= x;
			cout << "? " << 1 << endl;
			cin >> x;
			Z ^= x;

			cout << "? " << 1 << endl;
			cin >> x;
			cout << "? " << A1 + 1 << endl;
			cin >> x;
			cout << "? " << 1 << endl;
			cin >> x;

			cout << "? " << N - K + 1 << endl;
			cin >> x;
			Z ^= x;
			cout << "? " << N - K - A2 + 1 << endl;
			cin >> x;
			Z ^= x;
			cout << "? " << N - K + 1 << endl;
			cin >> x;
			Z ^= x;

			cout << "! " << Z << endl;
		}
	}

	return 0;
}
