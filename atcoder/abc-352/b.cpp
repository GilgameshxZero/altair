#if defined(__GNUC__) && !defined(__clang__)
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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S, T;
	cin >> S >> T;
	reverse(T.begin(), T.end());
	LL Y{0};
	RF(i, 0, S.length()) {
		if (S[i] != T.back()) {
			Y++;
			i--;
			T.pop_back();
			continue;
		}
		T.pop_back();
		cout << i + 1 + Y << ' ';
	}

	return 0;
}
