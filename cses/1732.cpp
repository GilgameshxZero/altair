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

LL const HASH_POWER{31}, HASH_PRIME{998244353};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	cin >> S;
	LL H[2]{0, 0}, P{1};
	RF(i, 1, S.length()) {
		H[0] = (H[0] * HASH_POWER + S[i - 1] - 'a' + 1) % HASH_PRIME;
		H[1] = (H[1] + (S[S.length() - i] - 'a' + 1) * P) % HASH_PRIME;
		if (H[0] == H[1]) {
			cout << i << ' ';
		}
		P = P * HASH_POWER % HASH_PRIME;
	}

	return 0;
}
