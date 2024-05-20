#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, f, t)                                      \
	for (LL x(f), _t(t), _d{x < _t ? 1LL : -1LL}; x != _t; \
			 x += _d)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		string W, S, T;
		cin >> N >> S;
		W = S;
		sort(S.begin(), S.end());
		T = S[0];
		RF(i, 1, N) {
			if (T.back() == S[i]) {
				continue;
			}
			T += S[i];
		}
		char R[128];
		RF(i, 0, T.size()) {
			R[T[i]] = T[T.size() - i - 1];
		}
		RF(i, 0, N) {
			W[i] = R[W[i]];
		}
		cout << W << '\n';
	}

	return 0;
}
