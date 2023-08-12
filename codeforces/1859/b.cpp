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
		vector<LL> A(N), B(N), C;
		LL Z{0}, G{LLONG_MAX / 2}, K{0};
		RF(i, 0, N) {
			LL m;
			cin >> m;
			C.resize(m);
			RF(j, 0, m) {
				cin >> C[j];
			}
			sort(C.begin(), C.end());
			A[i] = C[0];
			B[i] = C[1] - C[0];
			G = min(G, A[i]);
			K += B[i];
		}
		RF(i, 0, N) {
			Z = max(Z, K - B[i] - (A[i] - G));
		}
		RF(i, 0, N) {
			Z += A[i];
		}
		cout << Z << '\n';
	}

	return 0;
}
