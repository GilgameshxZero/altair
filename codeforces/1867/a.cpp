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
		vector<pair<LL, LL>> A(N);
		RF(i, 0, N) {
			cin >> A[i].first;
			A[i].second = i;
		}
		sort(A.begin(), A.end());
		RF(i, N, 0) {
			A[N - i].first = i;
		}
		sort(A.begin(), A.end(), [](pair<LL, LL> &x, pair<LL, LL> &y) {
			return x.second < y.second;
		});
		RF(i, 0, N) {
			cout << A[i].first << ' ';
		}
		cout << '\n';
	}

	return 0;
}