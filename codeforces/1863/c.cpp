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
		LL N, K;
		cin >> N >> K;

		unordered_set<LL> S;
		RF(i, 0, N + 1) {
			S.insert(i);
		}
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
			S.erase(A[i]);
		}
		A.push_back(*S.begin());
		RF(
			i, (N + 1 - K % (N + 1)) % (N + 1), (N + 1 - K % (N + 1)) % (N + 1) + N) {
			cout << A[i % (N + 1)] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
