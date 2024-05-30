#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, f, t)                                      \
	for (LL x(f), _t(t), _d{x < _t ? 1LL : -1LL}; x != _t; \
			 x += _d)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL Z{1}, N;
		cin >> N;
		vector<LL> A(N), B(N + 1);
		RF(i, 0, N) {
			cin >> A[i];
		}
		RF(i, 0, N + 1) {
			cin >> B[i];
		}
		LL C{LLONG_MAX};
		RF(i, 0, N) {
			Z += abs(A[i] - B[i]);
			if (
				B.back() >= min(A[i], B[i]) &&
				B.back() <= max(A[i], B[i])) {
				C = 0;
			} else {
				C = min(
					{C, abs(B.back() - A[i]), abs(B.back() - B[i])});
			}
		}
		cout << Z + C << '\n';
	}

	return 0;
}
