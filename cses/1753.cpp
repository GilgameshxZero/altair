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

LL HASH_POWER{31}, HASH_PRIME{1000000021};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S, T;
	cin >> S >> T;

	LL HPP{1};
	RF(i, 0, T.size()) {
		HPP = HPP * HASH_POWER % HASH_PRIME;
	}
	LL H{0};
	RF(i, 0, T.size()) {
		H = (H * HASH_POWER + T[i] - 'a' + 1) % HASH_PRIME;
	}
	LL X{0}, Z{0};
	RF(i, 0, S.size()) {
		X = X * HASH_POWER + S[i] - 'a' + 1;
		if (i >= T.size()) {
			X -= HPP * (S[i - T.size()] - 'a' + 1);
		}
		X = (X % HASH_PRIME + HASH_PRIME) % HASH_PRIME;
		if (X == H) {
			Z++;
		}
	}
	cout << Z;

	return 0;
}
