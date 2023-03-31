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
		LL N, C, D;
		cin >> N >> C >> D;

		unordered_set<LL> S;
		LL ans{C * N + D};
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		sort(A.begin(), A.end());
		RF(i, 0, N) {
			S.insert(A[i]);
			ans = min(
				ans,
				(i + 1 - (LL)S.size()) * C + (N - (i + 1)) * C +
					(A[i] - (LL)S.size()) * D);
		}
		cout << ans << '\n';
	}

	return 0;
}
