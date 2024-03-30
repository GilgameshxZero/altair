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
		cin >> N >> K;
		vector<vector<LL>> A(N, vector<LL>(N));
		RF(i, 0, N) {
			RF(j, i, N) {
				cin >> A[i][j];
			}
		}
		vector<vector<LL>> E(N);
		RF(i, 0, N) {
			priority_queue<pair<LL, pair<LL, LL>>> q;
			RF(j, i, -1) {
				if (j >= 2 && !E[j - 2].empty()) {
					q.push({(A[j][i] + E[j - 2][0]), {j, 0}});
				} else {
					q.push({A[j][i], {-2, 0}});
				}
			}
			if (i > 0) {
				q.push({E[i - 1][0], {-1, 0}});
			} else {
				q.push({0, {-2, 0}});
			}
			while (!q.empty() && E[i].size() < K) {
				auto p{q.top()};
				q.pop();
				E[i].push_back(p.first);
				if (p.second.first == -2) {
					continue;
				} else if (
					p.second.first == -1 && p.second.second + 1 < E[i - 1].size()) {
					p.first = E[i - 1][p.second.second + 1];
					p.second.second++;
					q.push(p);
				} else if (
					p.second.first >= 0 &&
					p.second.second + 1 < E[p.second.first - 2].size()) {
					p.first =
						(A[p.second.first][i] + E[p.second.first - 2][p.second.second + 1]);
					p.second.second++;
					q.push(p);
				}
			}
		}

		RF(i, 0, K) {
			cout << E[N - 1][i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
