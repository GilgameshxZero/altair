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
	vector<LL> A(N), B(M);
	RF(i, 0, N) {
		cin >> A[i];
	}
	RF(i, 0, M) {
		cin >> B[i];
	}

	vector<vector<pair<LL, pair<LL, LL>>>> Z(N + 1);
	RF(i, 0, N + 1) {
		Z[i].resize(M + 1);
		Z[i].back() = {0, {-1, -1}};
	}
	RF(i, 0, M + 1) {
		Z.back()[i] = {0, {-1, -1}};
	}
	RF(i, N - 1, -1) {
		RF(j, M - 1, -1) {
			if (A[i] == B[j]) {
				Z[i][j] = {1 + Z[i + 1][j + 1].first, {i, j}};
			} else {
				Z[i][j] = {0, {-1, -1}};
			}
			if (Z[i + 1][j].first > Z[i][j].first) {
				Z[i][j] = Z[i + 1][j];
			}
			if (Z[i][j + 1].first > Z[i][j].first) {
				Z[i][j] = Z[i][j + 1];
			}
		}
	}
	cout << Z[0][0].first << '\n';
	pair<LL, LL> C{Z[0][0].second};
	while (C.first != -1) {
		cout << A[C.first] << ' ';
		C = Z[C.first + 1][C.second + 1].second;
	}
	
	return 0;
}
