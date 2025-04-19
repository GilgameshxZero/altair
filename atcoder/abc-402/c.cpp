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

	vector<vector<LL>> D(N);
	vector<LL> X(M);
	RF(i, 0, M) {
		cin >> X[i];
		RF(j, 0, X[i]) {
			LL A;
			cin >> A;
			D[A - 1].push_back(i);
		}
	}

	LL Z{0};
	RF(i, 0, N) {
		LL B;
		cin >> B;
		RF(i, 0, D[B - 1].size()) {
			if (--X[D[B - 1][i]] == 0) {
				Z++;
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
