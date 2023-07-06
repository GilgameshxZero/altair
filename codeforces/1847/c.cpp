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

		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}

		bitset<256> P;
		LL X{0};
		RF(i, N - 1, -1) {
			X ^= A[i];
			P[X] = true;
		}
		vector<LL> R;
		RF(i, 0, 256) {
			if (P[i]) {
				R.push_back(i);
			}
		}

		LL Z{0};
		RF(i, 0, R.size()) {
			Z = max(Z, R[i]);
			RF(j, i + 1, R.size()) {
				Z = max(Z, R[i] ^ R[j]);
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
