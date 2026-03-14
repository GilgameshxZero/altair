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

void solve(
	vector<vector<LL>> &E,
	LL K,
	vector<LL> &Y,
	LL i,
	LL par) {
	vector<LL> s;
	for (auto &j : E[i]) {
		if (j == par) {
			continue;
		}
		solve(E, K, Y, j, i);
		s.push_back(Y[j]);
	}
	if (s.empty()) {
		Y[i] = 0;
		return;
	}
	if (s.size() == 1) {
		Y[i] = s[0] + 1;
		return;
	}
	sort(s.begin(), s.end());
	if (s[0] + s[1] + 1 <= K) {
		Y[i] = 0;
	} else {
		Y[i] = s[0] + 1;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N, K, V;
		cin >> N >> K >> V;
		vector<vector<LL>> E(N);
		RF(i, 0, N - 1) {
			LL u, v;
			cin >> u >> v;
			u--;
			v--;
			E[u].push_back(v);
			E[v].push_back(u);
		}
		vector<LL> Y(N);
		solve(E, K, Y, V - 1, -1);
		// RF(i, 0, N) {
		// 	cout << Y[i] << ' ';
		// }
		// cout << '\n';
		cout << (Y[V - 1] == 0 ? "YES" : "NO") << '\n';
	}

	return 0;
}
