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
		LL P;
		cin >> P;
		vector<LL> Y;
		RF(i, 0, N - 1) {
			LL X;
			cin >> X;
			Y.push_back(abs(P - X));
			P = X;
		}
		sort(Y.begin(), Y.end());
		RF(i, 0, K - 1) {
			Y.pop_back();
		}
		LL Z{0};
		RF(i, 0, Y.size()) {
			Z += Y[i];
		}
		cout << Z << '\n';
	}

	return 0;
}
