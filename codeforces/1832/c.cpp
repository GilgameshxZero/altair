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

		vector<LL> A;
		RF(i, 0, N) {
			LL X;
			cin >> X;
			if (A.empty() || X != A.back()) {
				A.push_back(X);
			}
		}
		if (A.size() == 1) {
			cout << 1 << '\n';
			continue;
		}
		LL Z{2};
		RF(i, 1, A.size() - 1) {
			if (
				A[i] > A[i - 1] && A[i] > A[i + 1] ||
				A[i] < A[i - 1] && A[i] < A[i + 1]) {
				Z++;
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
