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

	LL N, X;
	cin >> N >> X;
	vector<pair<LL, LL>> A(N);
	RF(i, 0, N) {
		cin >> A[i].first;
		A[i].second = i;
	}
	sort(A.begin(), A.end());
	RF(i, 0, N) {
		if (i >= A.size() - 1) {
			break;
		}
		if (A[i].first + A.back().first > X) {
			A.pop_back();
			i--;
			continue;
		}
		if (A[i].first + A.back().first < X) {
			continue;
		}
		cout << A[i].second + 1 << ' ' << A.back().second + 1;
		return 0;
	}
	cout << "IMPOSSIBLE";

	return 0;
}
