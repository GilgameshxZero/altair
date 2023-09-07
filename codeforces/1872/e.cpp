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
		LL Z{0};
		string S;
		cin >> S;
		RF(i, 0, N) {
			if (S[i] == '0') {
				Z ^= A[i];
			}
		}
		vector<LL> B(N);
		B[0] = A[0];
		RF(i, 1, N) {
			B[i] = B[i - 1] ^ A[i];
		}
		LL Q;
		cin >> Q;
		RF(i, 0, Q) {
			LL X;
			cin >> X;
			if (X == 1) {
				LL L, R;
				cin >> L >> R;
				L--;
				R--;
				Z ^= B[R] ^ (L == 0 ? 0 : B[L - 1]);
			} else {
				LL Y;
				cin >> Y;
				if (Y == 0) {
					cout << Z << ' ';
				} else {
					cout << (Z ^ B[N - 1]) << ' ';
				}
			}
		}
		cout << '\n';
	}

	return 0;
}
