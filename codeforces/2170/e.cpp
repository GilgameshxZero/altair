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

LL const MOD{998244353};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, M;
		cin >> N >> M;
		vector<pair<LL, LL>> LR(M);
		RF(i, 0, M) {
			cin >> LR[i].second >> LR[i].first;
		}
		sort(LR.begin(), LR.end());

		vector<LL> STP(N + 1);
		LL LRI{0}, MB{0}, MBX;
		bool F{false};
		RF(i, 1, N + 1) {
			MBX = MB;
			for (; LRI < M && LR[LRI].first <= i; LRI++) {
				MBX = max(MBX, LR[LRI].second);
				F = true;
			}

			STP[i] = (MOD + STP[i - 1] + (STP[i - 1] - STP[MB] + !F * 2)) % MOD;
			MB = MBX;

			RF(j, 1, i + 1) {
				cout << (MOD + STP[j] - STP[j - 1]) % MOD << ' ';
			}
			cout << '\n';
		}
		cout << (MOD + STP[N] - STP[MB]) % MOD << '\n';
	}

	return 0;
}
