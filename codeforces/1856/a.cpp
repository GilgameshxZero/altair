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
		map<LL, vector<LL>> B;
		RF(i, 0, N) {
			cin >> A[i];
			B[A[i]].push_back(i);
		}
		LL C{0};
		RF(i, 0, N - 1) {
			C += A[i] > A[i + 1];
		}
		if (C == 0) {
			cout << "0\n";
			continue;
		}
		for (auto &i : B) {
			for (auto &j : i.second) {
				if (j != 0) {
					C -= A[j - 1] > A[j];
				}
				if (j != N - 1) {
					C -= A[j] > A[j + 1];
				}
				A[j] = 0;
				if (j != 0) {
					C += A[j - 1] > A[j];
				}
				if (j != N - 1) {
					C += A[j] > A[j + 1];
				}
			}
			if (C == 0) {
				cout << i.first << '\n';
				break;
			}
		}
	}

	return 0;
}
