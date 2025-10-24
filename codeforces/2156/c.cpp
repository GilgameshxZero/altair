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

array<LL, 200001> C;

int main() {
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
			C[A[i]]++;
		}
		sort(A.begin(), A.end());
		LL Z{1};
		RF(i, N, 1) {
			LL c{0};
			for (LL j{i}; j <= min(N, 4 * i - 1); j += i) {
				c += C[j];
			}
			auto j{lower_bound(A.begin(), A.end(), 4 * i)};
			c += A.end() - j;
			if (K + c >= N) {
				Z = i;
				break;
			}
		}
		cout << Z << '\n';
		RF(i, 0, N) {
			C[A[i]]--;
		}
	}

	return 0;
}
