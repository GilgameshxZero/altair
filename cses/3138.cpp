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

	vector<pair<pair<LL, LL>, LL>> X;
	if (S[N] == S[N - 1]) {
		X.push_back({{N, N + 1}, -(N - 1)});
	} else {
		X.push_back({{N, N + 1}, N});
	}
	RF(i, N - 1, 0) {
		LL low, high{1}, mid;
		for (; high <= min(i, N - i); high *= 2) {
			if (
				getLeftHash(i, high) != getRightHash(i + 1, high)) {
				break;
			}
		}
		low = high / 2;
		high = min({high, i + 1, N - i + 1});
		while (low + 1 < high) {
			mid = (low + high) / 2;
			if (getLeftHash(i, mid) != getRightHash(i + 1, mid)) {
				high = mid;
			} else {
				low = mid;
			}
		}
		X.push_back({{i + 1, i + low + 1}, -i});

		high = 1;
		for (; high <= min(i - 1, N - i); high *= 2) {
			if (
				getLeftHash(i - 1, high) !=
				getRightHash(i + 1, high)) {
				break;
			}
		}
		low = high / 2;
		high = min({high, i, N - i + 1});
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
		X.push_back({{i + 1, i + low + 1}, i});
	}

	set<pair<LL, pair<pair<LL, LL>, LL>>> Y;
	sort(X.begin(), X.end());
	reverse(X.begin(), X.end());
	RF(i, 1, N + 1) {
		while (!X.empty() && X.back().first.first <= i) {
			Y.insert(
				{X.back().first.first * 2 + (X.back().second <= 0),
				 X.back()});
			X.pop_back();
		}
		while (!Y.empty() &&
					 Y.begin()->second.first.second <= i) {
			Y.erase(Y.begin());
		}
		if (Y.empty()) {
			cout << "1 ";
		} else {
			LL center{Y.begin()->second.second};
			cout << (center < 0 ? 2 * (i + center)
													: 1 + 2 * (i - center))
					 << ' ';
		}
	}

	return 0;
}
