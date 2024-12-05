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

void place(vector<vector<LL>> &Z, LL r, LL p) {
	if (r == 0) {
		Z.push_back(Z.back());
		return;
	}
	RF(i, r - 2, p) {
		Z.back().push_back(i + 1);
		place(Z, r - 1, i);
		Z.back().pop_back();
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, M;
	cin >> N >> M;
	LL X{M - 1 - 10 * (N - 1)};
	vector<vector<LL>> Z;
	Z.push_back({});
	place(Z, X, X + N - 1);

	Z.pop_back();
	cout << Z.size() << '\n';
	RF(i, 0, Z.size()) {
		vector<LL> Y;
		Y.push_back(M);
		RF(j, 0, X + N) {
			if (!Z[i].empty() && j == Z[i].back()) {
				Z[i].pop_back();
				Y.back()--;
			} else {
				Y.push_back(Y.back() - 10);
			}
		}
		Y.pop_back();
		RF(i, Y.size() - 1, -1) {
			cout << Y[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
