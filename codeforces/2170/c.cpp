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
		LL N, K;
		cin >> N >> K;
		vector<LL> B(N);
		multiset<LL> A;
		RF(i, 0, N) {
			LL I;
			cin >> I;
			A.insert(I);
		}
		RF(i, 0, N) {
			cin >> B[i];
		}
		sort(B.begin(), B.end());
		LL Z{0};
		RF(i, 0, N) {
			LL Y{B[i] + 1}, W{(K - B[i]) / Y};
			auto J{A.upper_bound(W)};
			if (J != A.begin()) {
				J--;
			}
			if (*J > W) {
				break;
			}
			A.erase(J);
			Z++;
		}
		cout << Z << '\n';
	}

	return 0;
}
