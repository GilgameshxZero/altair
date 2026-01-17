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

void dfs(
	vector<vector<LL>> &E,
	vector<LL> &P,
	vector<LL> &D,
	LL cur,
	LL par) {
	P[cur] = par;
	for (auto &i : E[cur]) {
		if (i == par) {
			continue;
		}
		D[i] = D[cur] + 1;
		dfs(E, P, D, i, cur);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N;
		cin >> N;
		vector<vector<LL>> E(N);
		RF(i, 0, N - 1) {
			LL u, v;
			cin >> u >> v;
			u--;
			v--;
			E[u].push_back(v);
			E[v].push_back(u);
		}
		vector<LL> D(N), P(N);
		D[0] = 0;
		dfs(E, P, D, 0, -1);
		vector<vector<LL>> L;
		RF(i, 0, N) {
			if ((LL)L.size() < D[i] + 1) {
				L.resize(D[i] + 1);
			}
			L[D[i]].push_back(i);
		}

		vector<LL> F, Y(N, -1);
		RF(i, L.size() - 1, 0) {
			vector<pair<LL, LL>> so;
			for (auto &j : L[i - 1]) {
				so.push_back({(LL)E[j].size(), j});
			}
			sort(so.begin(), so.end());
			vector<LL> s;
			for (auto &j : so) {
				s.push_back(j.second);
			}

			queue<LL> q;
			for (auto &j : s) {
				q.push(j);
			}

			vector<LL> f;
			for (auto &j : s) {
				for (auto &k : E[j]) {
					if (k == P[j]) {
						continue;
					}
					if (q.empty()) {
						f.push_back(k);
						continue;
					}
					if (P[k] == q.front()) {
						q.push(q.front());
						q.pop();
					}
					if (P[k] == q.front()) {
						f.push_back(k);
						continue;
					}
					Y[q.front()] = k;
					q.pop();
				}
				if (!q.empty() && j == q.front()) {
					q.push(q.front());
					q.pop();
				}
			}

			RF(j, 0, min((LL)F.size(), (LL)q.size())) {
				Y[q.front()] = F.back();
				q.pop();
				F.pop_back();
			}
			F.insert(F.end(), f.begin(), f.end());
		}
		F.push_back(0);
		cout << F.size() << '\n';
		for (auto &i : F) {
			LL c{i};
			vector<LL> y;
			while (c != -1) {
				y.push_back(c + 1);
				c = Y[c];
			}
			cout << y.size() << ' ';
			for (auto &j : y) {
				cout << j << ' ';
			}
			cout << '\n';
		}
	}

	return 0;
}
