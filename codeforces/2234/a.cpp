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
		sort(A.begin(), A.end());
		bool fail{false};
		RF(i, 0, N - 2) {
			if (A[i + 2] % A[i + 1] != A[i]) {
				fail = true;
				break;
			}
		}
		if (fail) {
			cout << "-1\n";
		} else {
			cout << A[N - 1] << ' ' << A[N - 2] << '\n';
		}
	}

	return 0;
}
