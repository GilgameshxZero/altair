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

	vector<vector<LL>> E(N);
	RF(i, 0, M) {
		LL X, Y;
		cin >> X >> Y;
		E[X - 1].push_back(Y - 1);
		E[Y - 1].push_back(X - 1);
	}

	queue<LL> S;
	vector<LL> P(N, -1);
	vector<bool> V(N);
	S.push(0);
	P[0] = 0;
	while (!S.empty()) {
		LL I{S.front()};
		S.pop();
		if (V[I]) {
			continue;
		}
		if (I == N - 1) {
			vector<LL> Z;
			while (I > 0) {
				Z.push_back(I);
				I = P[I];
			}
			Z.push_back(I);
			reverse(Z.begin(), Z.end());
			cout << Z.size() << '\n';
			RF(i, 0, Z.size()) {
				cout << Z[i] + 1 << ' ';
			}
			return 0;
		}
		V[I] = true;
		RF(i, 0, E[I].size()) {
			if (P[E[I][i]] == -1) {
				P[E[I][i]] = I;
				S.push(E[I][i]);
			}
		}
	}
	cout << "IMPOSSIBLE";

	return 0;
}
