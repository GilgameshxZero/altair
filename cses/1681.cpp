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

	vector<vector<LL>> E(N), R(N);
	vector<LL> ID(N);
	RF(i, 0, M) {
		LL A, B;
		cin >> A >> B;
		A--;
		B--;
		E[A].push_back(B);
		R[B].push_back(A);
		ID[B]++;
	}

	queue<LL> Q;
	RF(i, 0, N) {
		if (ID[i] == 0) {
			Q.push(i);
		}
	}
	vector<LL> X(N);
	vector<bool> W(N);
	W[0] = true;
	X[0] = 1;
	while (!Q.empty()) {
		LL j{Q.front()};
		Q.pop();
		for (auto &i : E[j]) {
			ID[i]--;
			if (ID[i] == 0) {
				for (auto &k : R[i]) {
					if (W[k]) {
						W[i] = true;
						X[i] += X[k];
						X[i] %= 1000000007;
					}
				}
				Q.push(i);
			}
		}
	}
	cout << X[N - 1];

	return 0;
}
