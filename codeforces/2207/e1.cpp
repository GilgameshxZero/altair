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
		vector<LL> A(N + 1);
		A[0] = N;
		RF(i, 1, N + 1) {
			cin >> A[i];
		}
		vector<LL> C(A);
		sort(C.begin(), C.end());
		reverse(C.begin(), C.end());
		if (A != C) {
			cout << "NO\n";
			continue;
		}
		vector<LL> B(N + 1), D;
		vector<bool> E(N + 1, true);
		RF(i, 0, N + 1) {
			E[A[i]] = false;
		}
		RF(i, 0, N + 1) {
			if (E[i]) {
				D.push_back(i);
			}
		}

		bool F{false};
		B[1] = N;
		RF(i, 1, N + 1) {
			if (A[i] == A[i - 1]) {
				B[i] = D.back();
				D.pop_back();
				if (B[i] > A[i]) {
					F = true;
				}
			} else {
				B[i] = B[1];
			}
		}

		if (F) {
			cout << "NO\n";
		} else {
			cout << "YES\n";
			RF(i, 1, N + 1) {
				cout << B[i] << ' ';
			}
			cout << '\n';
		}
	}

	return 0;
}
