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

	LL N, M;
	cin >> N >> M;
	RF(i, 0, N) {
		string S;
		cin >> S;
		RF(j, 0, M) {
			cout << (char)((S[j] - 'A' + 1) % 2 + ((i + j) % 2 ? 'A' : 'C'));
		}
		cout << '\n';
	}

	return 0;
}
