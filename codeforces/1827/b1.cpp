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

		LL ZT{0};
		vector<vector<LL>> Z(N);
		Z[0].push_back(0);
		RF(i, 1, N) {
			Z[i].push_back(0);
			LL S{A[i]}, Q{A[i]}, B{i};
			RF(j, 1, i + 1) {
				Q = min(Q, A[i - j]);
				if (A[i - j] < S) {
					Z[i].push_back(Z[i][i - B] + Z[B - 1][B - (i - j) - 1] + 1);
				} else {
					S = Q;
					B = i - j;
					Z[i].push_back(0);
				}
				ZT += j - Z[i].back();
			}
		}

		cout << ZT << '\n';
	}

	return 0;
}
