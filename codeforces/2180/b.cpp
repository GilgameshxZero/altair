#if defined(__GNUC__) && !defined(__clang__) && !defined(__MINGW32__)
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
		cin >> N;
		vector<string> S(N);
		RF(i, 0, N) {
			cin >> S[i];
		}
		string Z, Y;
		RF(i, 0, N) {
			Y = S[i] + Z;
			Z += S[i];
			if (Y < Z) {
				swap(Z, Y);
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
