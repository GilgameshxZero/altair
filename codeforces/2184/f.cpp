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

void dfs(vector<vector<LL>> &E, vector<LL> &X, LL c, LL p) {
	X[c] = 2;
	if (p != -1 && E[c].size() == 1) {
		return;
	}
	LL ups{0}, downs{0}, cc{0};
	for (auto &i : E[c]) {
		if (i == p) {
			continue;
		}
		dfs(E, X, i, c);
		cc++;
		ups += (X[i] & 4) != 0;
		downs += (X[i] & 1) != 0;
	}
	RF(i, 0, min(ups, 2LL) + 1) {
		RF(j, 0, min(downs, 2LL) + 1) {
			X[c] |= (1LL << ((cc + i + j * 2) % 3));
		}
	}
	// cout << c << ": " << X[c] << ' ' << cc << ' ' << ups
	// 		 << ' ' << downs << '\n';
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
			LL U, V;
			cin >> U >> V;
			U--;
			V--;
			E[U].push_back(V);
			E[V].push_back(U);
		}
		vector<LL> X(N);
		dfs(E, X, 0, -1);
		cout << ((X[0] & 1) ? "YES" : "NO") << '\n';
	}

	return 0;
}
