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
		LL N, K;
		string S;
		cin >> N >> K >> S;
		if (K % 2 == 0) {
			sort(S.begin(), S.end());
			cout << S << '\n';
		} else {
			string R[2];
			RF(i, 0, N) {
				R[i % 2].push_back(S[i]);
			}
			sort(R[0].begin(), R[0].end());
			sort(R[1].begin(), R[1].end());
			RF(i, 0, N) {
				S[i] = R[i % 2][i / 2];
			}
			cout << S << '\n';
		}
	}

	return 0;
}
