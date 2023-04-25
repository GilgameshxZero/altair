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
		string A;
		cin >> A;

		vector<vector<LL>> Z(A.size() + 1, vector<LL>(A.size(), -1));
		RF(i, 1, A.size() + 1) {
			if (i % 2 != 0) {
				continue;
			}
			RF(j, 0, A.size() - i + 1) {
				if (i == 2) {
					Z[i][j] = A[j] == A[j + 1] ? 1 : 0;
					continue;
				}

				Z[i][j] = min(
					max(
						Z[i - 2][j + 2] == 1
							? (A[j] < A[j + 1] ? 0 : (A[j] > A[j + 1] ? 2 : 1))
							: Z[i - 2][j + 2],
						Z[i - 2][j + 1] == 1
							? (A[j] < A[j + i - 1] ? 0 : (A[j] > A[j + i - 1] ? 2 : 1))
							: Z[i - 2][j + 1]),
					max(
						Z[i - 2][j] == 1 ? (A[j + i - 1] < A[j + i - 2]
																	? 0
																	: (A[j + i - 1] > A[j + i - 2] ? 2 : 1))
														 : Z[i - 2][j],
						Z[i - 2][j + 1] == 1
							? (A[j + i - 1] < A[j] ? 0 : (A[j + i - 1] > A[j] ? 2 : 1))
							: Z[i - 2][j + 1]));
			}
		}

		cout << (Z[A.size()][0] == 0 ? "Alice"
																 : (Z[A.size()][0] == 2 ? "Bob" : "Draw"))
				 << '\n';
	}

	return 0;
}
