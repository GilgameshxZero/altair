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
		LL N, K;
		cin >> N >> K;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		sort(A.begin(), A.end());
		LL S{0};
		RF(i, 2 * K, N) {
			S += A[i];
		}
		LL Z{S};
		RF(i, 0, K) {
			S -= A[N - 1 - i];
			S += A[2 * K - 1 - i * 2];
			S += A[2 * K - 2 - i * 2];
			Z = max(Z, S);
		}
		cout << Z << '\n';
	}

	return 0;
}
