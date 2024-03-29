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
		LL N, M, K;
		cin >> N >> M >> K;

		vector<LL> A(K);
		RF(i, 0, K) {
			cin >> A[i];
		}
		sort(A.begin(), A.end());
		reverse(A.begin(), A.end());

		auto attempt{[&](LL X, LL Y) {
			LL rem{0};
			auto B(A);
			RF(i, 0, A.size()) {
				if (X < 2) {
					break;
				}
				if (B[i] < 2 * Y) {
					break;
				}
				X -= 2;
				B[i] -= 2 * Y;
				rem += (B[i]) / Y;
			}
			if (rem >= X) {
				return true;
			} else {
				return false;
			}
		}};

		cout << (attempt(N, M) || attempt(M, N) ? "Yes\n" : "No\n");
	}

	return 0;
}
