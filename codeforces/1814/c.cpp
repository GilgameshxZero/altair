#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, S1, S2;
		cin >> N >> S1 >> S2;

		vector<pair<LL, LL>> R(N);
		RF(i, 0, N) {
			cin >> R[i].first;
			R[i].second = i;
		}
		sort(R.begin(), R.end());
		reverse(R.begin(), R.end());

		vector<pair<LL, pair<LL, LL>>> P;
		RF(i, 0, N) {
			P.push_back({S1 * (i + 1), {0, i}});
			P.push_back({S2 * (i + 1), {1, i}});
		}
		sort(P.begin(), P.end());

		vector<LL> A[2];
		RF(i, 0, N) {
			A[P[i].second.first].push_back(R[i].second);
		}
		cout << A[0].size();
		RF(i, 0, A[0].size()) {
			cout << ' ' << A[0][i] + 1;
		}
		cout << '\n' << A[1].size();
		RF(i, 0, A[1].size()) {
			cout << ' ' << A[1][i] + 1;
		}
		cout << '\n';
	}

	return 0;
}
