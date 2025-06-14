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

	LL N, M;
	cin >> N >> M;
	LL X{1024};
	vector<vector<LL>> E(N * X);
	RF(i, 0, M) {
		LL A, B, W;
		cin >> A >> B >> W;
		A--;
		B--;
		RF(j, 0, X) {
			E[A * X + j].push_back(B * X + (j ^ W));
		}
	}

	queue<LL> Q;
	Q.push(0);
	vector<bool> V(N * X);
	while (!Q.empty()) {
		LL Y{Q.front()};
		Q.pop();
		if (V[Y]) {
			continue;
		}
		V[Y] = true;
		RF(i, 0, E[Y].size()) {
			Q.push(E[Y][i]);
		}
	}

	RF(i, 0, X) {
		if (V[(N - 1) * X + i]) {
			cout << i;
			return 0;
		}
	}
	cout << -1;

	return 0;
}
