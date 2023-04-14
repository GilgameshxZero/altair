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

int main(int, char const *[]) {
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
		LL lnz{N - 1};
		while (lnz >= 0 && A[lnz] == 0) {
			lnz--;
		}
		lnz++;

		if (lnz == 0) {
			cout << "Yes\n";
			continue;
		} else if (lnz == 1) {
			cout << (A[0] == 0 ? "Yes" : "No") << '\n';
			continue;
		}

		vector<LL> X(lnz), B(lnz);
		B[0] = A[0];
		RF(i, 1, lnz - 1) {
			B[i] = A[i] + 1;
		}
		B[lnz - 1] = A[lnz - 1];
		bool possible{true};
		X[0] = B[0] - 1;
		possible &= X[0] >= 0;
		RF(i, 1, lnz - 1) {
			X[i] = B[i] - 1 + X[i - 1];
			if (X[i] < 0) {
				possible = false;
				break;
			}
		}
		possible &= B[lnz - 1] == -X[lnz - 2] - 1;
		cout << (possible ? "Yes" : "No") << '\n';
	}

	return 0;
}
