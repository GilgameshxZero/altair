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
		RF(i, 0, N) {
			cin >> A[i];
		}
		A.push_back(1000000000);

		LL Z[3]{-1000000, -1000000, 0};
		RF(i, 0, A.size()) {
			Z[0] = max(Z[0], Z[1]);
			if (Z[0] > A[i]) {
				Z[0]--;
			} else if (Z[0] < A[i]) {
				Z[0]++;
			}
			Z[1] = max(Z[1], Z[2]);
			if (Z[2] > A[i]) {
				Z[2]--;
			} else if (Z[2] < A[i]) {
				Z[2]++;
			}
		}
		cout << Z[0] - 1<< '\n';
	}

	return 0;
}
