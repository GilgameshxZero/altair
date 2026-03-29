#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N, M;
		cin >> N >> M;
		vector<LL> R(N * M), C(N * M);
		RF(i, 0, N * M) {
			cin >> R[i];
		}
		RF(i, 0, N * M) {
			cin >> C[i];
			C[i]--;
		}
		vector<vector<LL>> CC(M);
		RF(i, 0, N * M) {
			CC[C[i]].push_back(R[i]);
		}

		vector<vector<LL>> X(M);
		RF(i, 0, M) {
			X[i].push_back(0);
			LL next{0};
			RF(j, 1, N + 1) {
				if (CC[i][next] <= j) {
					next++;
				} else {
					X[i].push_back(j);
				}
			}
			X[i].push_back(N + 1);
		}
		set<LL> XS;
		RF(i, 0, M) {
			RF(j, 0, X[i].size()) {
				XS.insert(X[i][j]);
			}
		}
		vector<LL> XX;
		for (auto &i : XS) {
			XX.push_back(i);
		}

		vector<LL> Y1(N + 2), Y2(N + 2);
		RF(i, 1, XX.size()) {
			LL c{1};
			RF(j, 0, M) {
				auto k{
					lower_bound(X[j].begin(), X[j].end(), XX[i - 1])};
				if (k != X[j].end() && *k == XX[i - 1]) {
					c++;
				}
			}
			Y2[XX[i]] =
				min({Y1[XX[i - 1]] + M + 1, Y2[XX[i - 1]] + c});
			Y1[XX[i]] = min(
				{Y2[XX[i]],
				 Y1[XX[i - 1]] + XX[i] - XX[i - 1],
				 Y2[XX[i - 1]] + c});
			// cout << Y[XX[i]] << ' ';
		}
		cout << Y1[N + 1] - 2 << '\n';
	}

	return 0;
}
