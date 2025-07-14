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

	LL H, W;
	cin >> H >> W;
	vector<string> S(H + 2);
	RF(i, 1, H + 1) {
		cin >> S[i];
		S[i] = "_" + S[i] + "_";
	}
	S[0] = S.back() = string(W + 2, '_');

	vector<pair<LL, LL>> D{
		{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
	string T{"snuke"};
	RF(i, 1, H + 1) {
		RF(j, 1, W + 1) {
			RF(k, 0, 8) {
				bool fail{false};
				RF(l, 0, 5) {
					if (S[i + D[k].first * l][j + D[k].second * l] != T[l]) {
						fail = true;
						break;
					}
				}
				if (!fail) {
					RF(l, 0, 5) {
						cout << i + D[k].first * l << ' ' << j + D[k].second * l << '\n';
					}
					return 0;
				}
			}
		}
	}

	return 0;
}
