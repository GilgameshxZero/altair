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
		cin >> N;
		vector<vector<LL>> B(2 * N + 2);
		vector<vector<bool>> C(2 * N + 2);
		RF(i, 0, N) {
			LL x;
			cin >> x;
			B[x].push_back(i);
			C[x].push_back(false);
		}
		LL Z{N};
		RF(i, 1, B.size() - 1) {
			LL k((LL)B[i - 1].size() - 1), l((LL)B[i + 1].size() - 1);
			vector<LL> K, L;
			RF(j, (LL)B[i].size() - 1, -1) {
				for (; k >= 0 && B[i - 1][k] > B[i][j]; k--) {
					if (!C[i - 1][k]) {
						K.push_back(k);
					}
				}
				for (; l >= 0 && B[i + 1][l] > B[i][j]; l--) {
					if (!C[i + 1][l]) {
						L.push_back(l);
					}
				}
				if (!K.empty()) {
					C[i - 1][K.back()] = true;
					K.pop_back();
					Z--;
				} else if (!L.empty()) {
					C[i + 1][L.back()] = true;
					L.pop_back();
					Z--;
				}
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
