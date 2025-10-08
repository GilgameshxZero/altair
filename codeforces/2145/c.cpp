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
		LL Y{0}, D{0};
		RF(i, 0, N) {
			Y += S[i] == 'a' ? 1 : -1;
		}

		unordered_map<LL, LL> M;
		LL Z{N};
		M[0] = -1;
		RF(i, 0, N) {
			D += S[i] == 'a' ? 1 : -1;
			M[D] = i;
			auto j{M.find(D - Y)};
			if (j != M.end()) {
				Z = min(Z, i - M[D - Y]);
			}
		}
		cout << (Z == N ? -1 : Z) << '\n';
	}

	return 0;
}
