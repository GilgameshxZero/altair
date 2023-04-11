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
		LL N, M;
		cin >> N >> M;

		vector<unordered_set<LL>> E[2];
		E[0].resize(N);
		E[1].resize(N);
		RF(i, 0, M) {
			LL A, B;
			cin >> A >> B;
			if (A == 1) {
				continue;
			}
			E[0][A - 1].insert(B - 1);
			E[1][B - 1].insert(A - 1);
		}

		queue<LL> Q;
		vector<bool> qd(N, false);
		vector<LL> best(N, INT_MAX);
		best[0] = 1;
		Q.push(0);
		qd[0] = true;
		while (!Q.empty()) {
			LL cur{Q.front()};
			Q.pop();
			for (auto &i : E[1][cur]) {
				best[i] = min(best[i], best[cur] + 1);
				if (!qd[i]) {
					Q.push(i);
					qd[i] = true;
				}
			}
		}
		LL ans{0};
		RF(i, 0, N) {
			ans += best[i];
		}

		if (ans >= INT_MAX) {
			cout << "INFINITE\n";
			continue;
		}
		cout << "FINITE\n" << ans << '\n';
		vector<vector<LL>> abest;
		RF(i, 0, N) {
			if (abest.size() < best[i]) {
				abest.resize(best[i]);
			}
			abest[best[i] - 1].push_back(i);
		}
		RF(i, 0, abest.size()) {
			RF(j, abest.size() - 1, i - 1) {
				RF(k, 0, abest[j].size()) {
					cout << abest[j][k] + 1 << ' ';
				}
			}
		}
		cout << '\n';
	}

	return 0;
}
