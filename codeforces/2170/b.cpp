#if defined(__GNUC__) && !defined(__clang__) && !defined(__MINGW32__)
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
		vector<LL> B(N);
		LL MS{0}, MT{0};
		RF(i, 0, N) {
			cin >> B[i];
			MS += B[i] >= 1;
			MT += max(0LL, B[i] - 1);
		}
		if (MT >= N - 1) {
			cout << MS << '\n';
		} else {
			cout << MS - (N - 1 - MT) << '\n';
		}
	}

	return 0;
}
