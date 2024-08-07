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

		LL S{0};
		vector<LL> B(N);
		RF(i, 0, N) {
			LL X;
			cin >> X;
			S += X;
		}
		RF(i, 0, N) {
			cin >> B[i];
			S += B[i];
		}
		sort(B.begin(), B.end());
		cout << S - B.back() << '\n';
	}

	return 0;
}
