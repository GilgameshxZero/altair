#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

#pragma hdrstop	 // ------------------------------------------------------------

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> A(N), B(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		RF(i, 0, N) {
			cin >> B[i];
		}
		RF(i, 0, N) {
			if (A[i] > B[i]) {
				swap(A[i], B[i]);
			}
		}
		bool possible{true};
		RF(i, 0, N) {
			possible &= A[i] <= A.back() && B[i] <= B.back();
		}
		cout << (possible ? "Yes" : "No") << '\n';
	}

	return 0;
}
