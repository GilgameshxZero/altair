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
		string S;
		cin >> N >> K >> S;

		array<LL, 26> F;
		F.fill(0);
		RF(i, 0, N) {
			F[S[i] - 'a']++;
		}

		string Z;
		RF(i, 0, K) {
			LL j{0};
			for (; j < min(26LL, N / K); j++) {
				if (F[j] == 0) {
					break;
				}
				F[j]--;
			}
			Z += 'a' + j;
		}
		cout << Z << '\n';
	}

	return 0;
}
