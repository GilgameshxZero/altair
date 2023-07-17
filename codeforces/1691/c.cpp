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
		vector<LL> P[2];
		RF(i, 0, N) {
			P[S[i] - '0'].push_back(i);
		}
		LL Z{0};
		RF(i, 0, N - 1) {
			Z += 10 * (S[i] - '0') + S[i + 1] - '0';
		}
		if (P[1].size() == 1) {
			if (N - 1 - P[1][0] <= K) {
				cout << 1 << '\n';
			} else if (P[1][0] <= K) {
				cout << 10 << '\n';
			} else {
				cout << 11 << '\n';
			}
			continue;
		}
		if (S.back() == '0') {
			if (!P[1].empty() && (N - 1) - P[1].back() <= K) {
				Z -= 10;
				K -= (N - 1) - P[1].back();
				P[1].pop_back();
			}
		}
		if (S[0] == '0') {
			if (!P[1].empty() && P[1][0] <= K) {
				Z--;
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
