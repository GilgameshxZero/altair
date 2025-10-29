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

void CY(vector<vector<LL>> &E, vector<LL> &Y, LL &Z, LL K, LL c, LL p) {
	LL N(E.size());
	Y[c] = 1;
	for (auto &i : E[c]) {
		if (i == p) {
			continue;
		}
		CY(E, Y, Z, K, i, c);
		Y[c] += Y[i];
		if (N - Y[i] >= K) {
			Z += Y[i];
		}
	}
	if (Y[c] >= K) {
		Z += N - Y[c];
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, K;
		cin >> N >> K;
		vector<vector<LL>> E(N);
		RF(i, 0, N - 1) {
			LL U, V;
			cin >> U >> V;
			U--;
			V--;
			E[U].push_back(V);
			E[V].push_back(U);
		}
		vector<LL> Y(N);
		LL Z{0};
		CY(E, Y, Z, K, 0, -1);
		cout << Z + N << '\n';
	}

	return 0;
}
