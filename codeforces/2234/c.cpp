#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
	// <https://codeforces.com/blog/entry/135127>.
	#include <string>
	#pragma GCC target("arch=core-avx2")
	#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for ( \
		LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
		x != _to; \
		x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N;
		cin >> N;
		vector<LL> A(N);
		RF(i, 0, N) { cin >> A[i]; }
		vector<LL> Z(N);
		RF(j, 0, N) {
			vector<LL> Y(N, LLONG_MAX);
			Y[0] = 0;
			Y[1] = A[0];
			RF(i, 2, N) {
				Y[i] = A[i - 1] > Y[i - 1] ? A[i - 1] : Y[i - 1];
			}
			Y[N - 1] = min(Y[N - 1], A[N - 1]);
			RF(i, N - 2, 0) {
				Y[i] = min(Y[i], A[i] > Y[i + 1] ? A[i] : Y[i + 1]);
			}

			RF(i, 0, N) { Z[j] += Y[i]; }
			LL a0{A[0]};
			RF(i, 0, N - 1) { A[i] = A[i + 1]; }
			A.back() = a0;
		}
		RF(i, 0, N) { cout << Z[i] << ' '; }
		cout << '\n';
	}

	return 0;
}
