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

unordered_map<LL, LL> oco;
vector<vector<LL>> E, EI;
vector<LL> A, P, PI;

void dfs(LL cur, LL par) {
	RF(i, 0, E[cur].size()) {
		if (E[cur][i] == par) {
			continue;
		}
		P[E[cur][i]] = cur;
		PI[E[cur][i]] = EI[cur][i];
		dfs(E[cur][i], cur);
	}
}

void collect(vector<LL> &bundle, LL cur, LL p1, LL p2) {
	RF(i, 0, E[cur].size()) {
		if (E[cur][i] == p1 || E[cur][i] == p2) {
			continue;
		}
		bundle.push_back(A[E[cur][i]]);
		collect(bundle, E[cur][i], cur, -1);
	}
}

void splay(unordered_map<LL, LL> &occ, set<LL> &elig, vector<LL> &bundle) {
	for (auto &i : bundle) {
		occ[i]++;
		if (occ[i] == 2) {
			elig.insert(i);
		}
	}
}

void desplay(unordered_map<LL, LL> &occ, set<LL> &elig, vector<LL> &bundle) {
	for (auto &i : bundle) {
		occ[i]--;
		if (occ[i] == 1) {
			elig.erase(i);
		}
	}
}

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	cin >> N;
	E.resize(N);
	EI.resize(N);
	A.resize(N);
	P.resize(N);
	PI.resize(N);

	RF(i, 0, N - 1) {
		LL U, V;
		cin >> U >> V;
		E[U - 1].push_back(V - 1);
		EI[U - 1].push_back(i);
		E[V - 1].push_back(U - 1);
		EI[V - 1].push_back(i);
	}
	RF(i, 0, N) {
		cin >> A[i];
		oco[A[i]]++;
	}

	LL mad{-1};
	for (auto &i : oco) {
		if (i.second >= 2 && (i.first > mad || mad == -1)) {
			mad = i.first;
		}
	}
	if (mad == -1) {
		RF(i, 0, N - 1) {
			cout << 0 << '\n';
		}
		return 0;
	}
	if (oco[mad] >= 3) {
		RF(i, 0, N - 1) {
			cout << mad << '\n';
		}
		return 0;
	}

	LL s1{-1}, s2;
	RF(i, 0, N) {
		if (A[i] == mad) {
			if (s1 == -1) {
				s1 = i;
			} else {
				s2 = i;
			}
		}
	}
	dfs(s1, -1);
	vector<LL> path, pathi;
	LL cur{s2};
	while (cur != s1) {
		path.push_back(cur);
		pathi.push_back(PI[cur]);
		cur = P[cur];
	}
	path.push_back(s1);
	reverse(path.begin(), path.end());
	reverse(pathi.begin(), pathi.end());

	vector<vector<LL>> bundles(path.size());
	RF(i, 1, path.size() - 1) {
		bundles[i].push_back(A[path[i]]);
		collect(bundles[i], path[i], path[i - 1], path[i + 1]);
	}
	bundles[0].push_back(A[path[0]]);
	collect(bundles[0], path[0], path[1], -1);
	bundles.back().push_back(A[path.back()]);
	collect(bundles.back(), path.back(), path[path.size() - 2], -1);

	unordered_map<LL, LL> occ1, occ2;
	set<LL> elig1, elig2;
	RF(i, 0, bundles.size()) {
		splay(occ2, elig2, bundles[i]);
	}

	vector<LL> ans(N - 1, mad);
	RF(i, 0, pathi.size()) {
		splay(occ1, elig1, bundles[i]);
		desplay(occ2, elig2, bundles[i]);
		if (elig1.empty() && elig2.empty()) {
			ans[pathi[i]] = 0;
		} else if (elig1.empty()) {
			ans[pathi[i]] = *elig2.rbegin();
		} else if (elig2.empty()) {
			ans[pathi[i]] = *elig1.rbegin();
		} else {
			ans[pathi[i]] = max(*elig1.rbegin(), *elig2.rbegin());
		}
	}
	RF(i, 0, N - 1) {
		cout << ans[i] << '\n';
	}

	return 0;
}
