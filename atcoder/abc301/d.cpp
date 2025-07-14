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

	string S;
	LL N;
	cin >> S >> N;
	
	LL T{0}, R{0};
	RF(i, 0, S.length()) {
		R = R * 2 + (S[i] == '1' ? 1 : 0);
	}
	RF(i, 0, S.length()) {
		R %= 1LL << (S.length() - 1 - i);
		if (S[i] == '0') {
			T *= 2;
		} else if (S[i] == '1') {
			T  = T * 2 + 1;
		} else {
			T = T * 2 + 1;
			if ((T << (S.length() - 1 - i)) + R > N) {
				T--;
			}
		}
	}
	if (T > N) {
		cout << -1;
	} else {
		cout << T;
	}

	return 0;
}
