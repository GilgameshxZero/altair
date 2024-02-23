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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		string S;
		cin >> N >> S;
		reverse(S.begin(), S.end());
		while (S.back() == '0') {
			S.pop_back();
		}
		reverse(S.begin(), S.end());
		string Z(S.size(), '0');
		LL carry{0};
		RF(i, 0, S.size()) {
			carry += S[i] - '0';
		}
		LL c2{0};
		RF(i, S.size() - 1, -1) {
			c2 += carry;
			Z[i] = '0' + (c2 % 10);
			c2 /= 10;
			carry -= S[i] - '0';
		}
		if (c2 > 0) {
			cout << c2;
		}
		cout << Z << '\n';
	}

	return 0;
}
