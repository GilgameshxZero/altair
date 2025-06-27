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

	LL N, M, K;
	cin >> N >> M >> K;
	vector<LL> A(N), B(M);
	RF(i, 0, N) {
		cin >> A[i];
	}
	RF(i, 0, M) {
		cin >> B[i];
	}
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	LL Z{0};
	while (!A.empty() && !B.empty()) {
		if (B.back() > A.back() + K) {
			B.pop_back();
		} else if (A.back() > B.back() + K) {
			A.pop_back();
		} else {
			Z++;
			A.pop_back();
			B.pop_back();
		}
	}
	cout << Z;

	return 0;
}
