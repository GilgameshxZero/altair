#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, y, z) for (LL x(y), c(z), d{x < c ? 1LL : -1LL}; x != c; x += d)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	cin >> N;
	LL Z{0};
	vector<LL> L(N), A(N);
	RF(i, 0, N) {
		cin >> A[i];
		A[i]--;
	}
	RF(i, 0, N) {
		LL w;
		cin >> w;
		if (w > L[A[i]]) {
			Z += L[A[i]];
			L[A[i]] = w;
		} else {
			Z += w;
		}
	}
	cout << Z << '\n';

	return 0;
}
