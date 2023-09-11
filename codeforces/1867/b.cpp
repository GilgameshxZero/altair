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
		LL mfb{0};
		RF(i, 0, N / 2) {
			mfb += S[i] != S[N - 1 - i];
		}
		string Z(N + 1, '0');
		RF(i, mfb, N + 1 - mfb) {
			if (N % 2 == 0) {
				Z[i] = i % 2 == mfb % 2 ? '1' : '0';
			} else {
				Z[i] = '1';
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
