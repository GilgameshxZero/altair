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
		LL R{0}, B{0};
		unordered_map<LL, LL> A;
		RF(i, 0, 2 * N) {
			LL X;
			cin >> X;
			A[X]++;
		}
		LL Z{0};
		for (auto &i : A) {
			if (i.second % 4 == 1 || i.second % 4 == 3) {
				Z++;
				R += i.second;
			} else if (i.second % 4 == 2) {
				Z += 2;
			} else {
				Z += 2;
				B = 2 - B;
			}
		}
		if (B > R) {
			Z -= 2;
		}
		cout << Z << '\n';
	}

	return 0;
}
