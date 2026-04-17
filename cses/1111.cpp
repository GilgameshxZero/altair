#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
// Bugfix: <https://codeforces.com/blog/entry/135127>.
#include <string>
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

LL const HASH_BASE{26}, HASH_MOD{1000000009};
vector<LL> HASH_POW;
vector<LL> preH, postH;

LL getLeftHash(LL end, LL len) {
	return (HASH_MOD + preH[end] -
					preH[end - len] * HASH_POW[len] % HASH_MOD) %
		HASH_MOD;
}
LL getRightHash(LL beg, LL len) {
	return (HASH_MOD + postH[beg] -
					postH[beg + len] * HASH_POW[len] % HASH_MOD) %
		HASH_MOD;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	cin >> S;
	LL N(S.length());
	HASH_POW.resize(N + 2);
	HASH_POW[0] = 1;
	RF(i, 1, N + 2) {
		HASH_POW[i] = HASH_POW[i - 1] * HASH_BASE % HASH_MOD;
	}
	S = "_" + S + "_";
	preH.resize(N + 2);
	postH.resize(N + 2);
	preH[0] = postH[N + 1] = 0;
	RF(i, 1, N + 1) {
		preH[i] = preH[i - 1] * HASH_BASE + S[i] - 'a';
		preH[i] %= HASH_MOD;
	}
	RF(i, N, 0) {
		postH[i] = postH[i + 1] * HASH_BASE + S[i] - 'a';
		postH[i] %= HASH_MOD;
	}

	pair<LL, LL> Z[2]{};
	Z[1] = {0, 1};
	RF(i, 1, N) {
		LL low, high{1}, mid;
		for (; high <= min(i, N - i); high *= 2) {
			if (
				getLeftHash(i, high) != getRightHash(i + 1, high)) {
				break;
			}
		}
		low = high / 2;
		high = min({i + 1, N - i + 1, high});
		while (low + 1 < high) {
			mid = (low + high) / 2;
			if (getLeftHash(i, mid) != getRightHash(i + 1, mid)) {
				high = mid;
			} else {
				low = mid;
			}
		}
		if (low > Z[0].first) {
			Z[0] = {low, i};
		}
		// cout << i << ' ' << low << '\n';
	}
	RF(i, 1, N + 1) {
		LL low, high{1}, mid;
		for (; high <= min(i - 1, N - i); high *= 2) {
			if (
				getLeftHash(i - 1, high) !=
				getRightHash(i + 1, high)) {
				break;
			}
		}
		low = high / 2;
		high = min({i + 1, N - i + 1, high});
		while (low + 1 < high) {
			mid = (low + high) / 2;
			if (
				getLeftHash(i - 1, mid) !=
				getRightHash(i + 1, mid)) {
				high = mid;
			} else {
				low = mid;
			}
		}
		if (low > Z[1].first) {
			Z[1] = {low, i};
		}
	}

	if (2 * Z[0].first > 1 + 2 * Z[1].first) {
		cout << S.substr(
							Z[0].second - Z[0].first + 1, 2 * Z[0].first)
				 << '\n';
	} else {
		cout << S.substr(
							Z[1].second - Z[1].first, 1 + 2 * Z[1].first)
				 << '\n';
	}

	return 0;
}
