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

	LL N, H, M;
	cin >> N >> H >> M;
	vector<pair<LL, LL>> A(N);
	RF(i, 0, N) {
		cin >> A[i].first >> A[i].second;
	}
	vector<array<LL, 3001>> X;
	X.push_back({});
	X.back().fill(0);
	RF(i, 0, A[0].second) {
		X.back()[i] = A[0].first;
	}
	RF(i, 1, N) {
		X.push_back({});
		X.back().fill(0);
		RF(j, 0, M + 1) {
			if (j < A[i].second) {
				X.back()[j] = A[i].first + X[i - 1][j];
				continue;
			}
			X.back()[j] = min(A[i].first + X[i - 1][j], X[i - 1][j - A[i].second]);
		}
		if (X.back()[M] > H) {
			X.pop_back();
			break;
		}
	}
	if (X.back()[M] > H) {
		X.pop_back();
	}
	cout << X.size();

	return 0;
}
