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
		vector<pair<LL, LL>> A;
		RF(i, 0, 3) {
			A.emplace_back(0, 0);
			cin >> A[i].first >> A[i].second;
			swap(A[i].first, A[i].second);
		}

		sort(A.begin(), A.end());
		reverse(A.begin(), A.end());
		LL S1{A[0].first};
		RF(i, 0, 3) {
			swap(A[i].first, A[i].second);
		}
		sort(A.begin(), A.end());
		reverse(A.begin(), A.end());
		LL S2{A[0].first};
		if (S1 > S2) {
			RF(i, 0, 3) {
				swap(A[i].first, A[i].second);
			}
			sort(A.begin(), A.end());
			reverse(A.begin(), A.end());
		}

		LL S{A[0].first}, R{S - A[0].second};
		bool fail = false;
		if (A[1].first == S && A[2].first == S) {
			fail = A[1].second + A[2].second != R;
		} else {
			if (A[1].second == R && A[2].second == R) {
				fail = A[1].first * A[1].second + A[2].first * A[2].second != R * S;
			} else {
				fail = true;
			}
		}

		cout << (fail ? "NO" : "YES") << '\n';
	}

	return 0;
}
