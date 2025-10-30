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
		LL N, X;
		cin >> N >> X;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		sort(A.begin(), A.end());

		vector<LL> Z;
		LL Y{0}, C{0}, ZZ{0};
		for (LL i{0}; i < A.size(); i++) {
			if (Y + A[i] < X) {
				Y += A[i];
				Z.push_back(A[i]);
				continue;
			}
			Y = (Y + A.back()) % X;
			Z.push_back(A.back());
			ZZ += A.back();
			A.pop_back();
			i--;
		}
		cout << ZZ << '\n';
		RF(i, 0, N) {
			cout << Z[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
