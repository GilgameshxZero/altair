#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N;
		cin >> N;
		vector<LL> A(N), B(N), C(N), D(N);
		RF(i, 0, N) {
			cin >> A[i];
			C[i] = abs(A[i]);
		}
		B.back() = A.back();
		D.back() = C.back();
		RF(i, N - 2, -1) {
			B[i] = A[i] + B[i + 1];
			D[i] = C[i] + D[i + 1];
		}
		LL Z{LLONG_MIN};
		Z = max(-B[1], A[0] + D[1] - D.back());
		RF(i, 1, N - 1) {
			Z = max(Z, A[0] + D[1] - D[i] - B[i + 1]);
		}
		cout << Z << '\n';
	}

	return 0;
}
