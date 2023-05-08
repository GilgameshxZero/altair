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

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		string S;
		cin >> N >> S;
		vector<pair<LL, LL>> Z;
		LL LP{0}, LD{1}, RP{2 * N - 1}, RD{-1}, LL{0}, RL{0};
		while (LP != RP) {
			for (; LP != RP && LL >= 0; LP += LD) {
				LL += (S[LP] == '(' ? 1 : -1);
			}
			for (; RP != LP && RL <= 0; RP += RD) {
				RL += (S[RP] == '(' ? 1 : -1);
			}
			if (LP == RP) {
				break;
			}
			LP -= LD;
			RP -= RD;
			Z.push_back({LP, RP});
			swap(LP, RP);
			swap(LD, RD);
			LL = RL = 0;
		}
		cout << Z.size() << '\n';
		for (auto &i : Z) {
			cout << i.first + 1 << ' ' << i.second + 1 << '\n';
		}
	}

	return 0;
}
