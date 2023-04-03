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

vector<vector<LL>> E;
vector<LL> H, P;

LL dfs(LL cur, LL par) {
	LL argans{0}, ans{cur};
	for (auto &i : E[cur]) {
		if (i == par) {
			continue;
		}
		H[i] = H[cur] + 1;
		P[i] = cur;
		LL cand{dfs(i, cur)};
		if (H[cand] > argans) {
			argans = H[cand];
			ans = cand;
		}
	}
	return ans;
}

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	cin >> N;
	E.resize(N);
	RF(i, 0, N - 1) {
		LL U, V;
		cin >> U >> V;
		E[U - 1].push_back(V - 1);
		E[V - 1].push_back(U - 1);
	}

	H.resize(N);
	P.resize(N);
	H[0] = 0;
	LL sr{dfs(0, -1)};
	H[sr] = 0;
	LL dia{dfs(sr, -1)};
	vector<LL> path;
	LL cur{dia};
	while (cur != sr) {
		path.push_back(cur);
		cur = P[cur];
	}
	path.push_back(sr);

	reverse(path.begin(), path.end());
	LL s1{path[path.size() / 2 - 1]}, s2{path[path.size() / 2]};
	fill(H.begin(), H.end(), -1);
	H[s1] = 0;
	LL hmax1{H[dfs(s1, s2)]};
	vector<LL> h1s(hmax1 + 1);
	RF(i, 0, N) {
		if (H[i] == -1) {
			continue;
		}
		h1s[H[i]]++;
	}

	fill(H.begin(), H.end(), -1);
	H[s2] = 0;
	LL hmax2{H[dfs(s2, s1)]};
	vector<LL> h2s(hmax2 + 1);
	RF(i, 0, N) {
		if (H[i] == -1) {
			continue;
		}
		h2s[H[i]]++;
	}

	if (h1s.size() < h2s.size()) {
		h1s.insert(h1s.begin(), 0);
	}
	vector<LL> ans(N + 1, N + 1);
	LL d{hmax1 + hmax2 + 1};
	RF(i, d, d - h1s.size()) {
		ans[i] = ans[i + 1] - h1s[h1s.size() - 1 - (d - i)] -
			h2s[h2s.size() - 1 - (d - i)];
	}
	RF(i, d + 1, N + 1) {
		ans[i] = N;
	}
	RF(i, 1, d - h1s.size() + 1) {
		ans[i] = 1;
	}
	RF(i, 1, N + 1) {
		cout << ans[i] << ' ';
	}

	return 0;
}
