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

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> A(N), C(N), I(N);
		RF(i, 0, N) {
			cin >> A[i];
			A[i]--;
			I[A[i]]++;
		}
		RF(i, 0, N) {
			cin >> C[i];
		}
		queue<LL> Q;
		RF(i, 0, N) {
			if (I[i] == 0) {
				Q.push(i);
			}
		}
		vector<bool> D(N, false);
		while (!Q.empty()) {
			LL i{Q.front()};
			Q.pop();
			cout << i + 1 << ' ';
			D[i] = true;
			I[A[i]]--;
			if (I[A[i]] == 0) {
				Q.push(A[i]);
			}
		}
		RF(i, 0, N) {
			if (D[i]) {
				continue;
			}
			vector<LL> Y;
			LL j{i};
			Y.push_back(j);
			while (A[j] != i) {
				j = A[j];
				Y.push_back(j);
			}
			LL y{0};
			RF(k, 0, Y.size()) {
				if (C[Y[k]] < C[Y[y]]) {
					y = k;
				}
			}
			RF(k, 0, Y.size()) {
				cout << Y[(k + y + 1) % Y.size()] + 1 << ' ';
				D[Y[k]] = true;
			}
		}
		cout << '\n';
	}

	return 0;
}
