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

void dfsCC(vector<set<LL>> &E, vector<LL> &I, vector<LL> &CCj, LL cur) {
	for (auto &i : E[cur]) {
		if (I[i] != -1) {
			continue;
		}
		CCj.push_back(i);
		I[i] = I[cur];
		dfsCC(E, I, CCj, i);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, M[2];
		cin >> N >> M[0] >> M[1];
		vector<set<LL>> E[2];
		RF(j, 0, 2) {
			E[j].resize(N);
			RF(i, 0, M[j]) {
				LL U, V;
				cin >> U >> V;
				U--;
				V--;
				E[j][U].insert(V);
				E[j][V].insert(U);
			}
		}

		vector<vector<LL>> CC[2];
		vector<LL> I[2];
		I[0].resize(N, -1);
		I[1].resize(N, -1);
		RF(j, 0, 2) {
			RF(i, 0, N) {
				if (I[j][i] == -1) {
					I[j][i] = CC[j].size();
					CC[j].push_back(vector<LL>());
					CC[j].back().push_back(i);
					dfsCC(E[j], I[j], CC[j].back(), i);
				}
			}
		}

		LL Z{0};
		RF(i, 0, CC[1].size()) {
			for (auto &j : CC[1][i]) {
				for (auto k{E[0][j].begin()}; k != E[0][j].end();) {
					if (I[1][*k] != i) {
						Z++;
						E[0][*k].erase(j);
						k = E[0][j].erase(k);
					} else {
						k++;
					}
				}
			}
		}

		vector<LL> IS(N, -1);
		RF(i, 0, CC[1].size()) {
			vector<vector<LL>> CCS;
			for (auto &j : CC[1][i]) {
				if (IS[j] == -1) {
					IS[j] = CCS.size();
					CCS.push_back(vector<LL>());
					CCS.back().push_back(j);
					dfsCC(E[0], IS, CCS.back(), j);
				}
			}
			Z += CCS.size() - 1;
		}

		cout << Z << '\n';
	}

	return 0;
}
