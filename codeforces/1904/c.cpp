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
		LL N, K;
		cin >> N >> K;
		vector<LL> A(N), B;
		unordered_set<LL> AM;
		RF(i, 0, N) {
			cin >> A[i];
			AM.insert(A[i]);
		}
		sort(A.begin(), A.end());
		if (K >= 3) {
			cout << 0 << '\n';
			continue;
		}
		bool id{false};
		RF(i, 1, N) {
			if (A[i] == A[i - 1]) {
				id = true;
				break;
			}
		}
		if (id) {
			cout << 0 << '\n';
			continue;
		}
		LL minB{LLONG_MAX};
		bool twoStep{false};
		RF(i, 0, N) {
			RF(j, i + 1, N) {
				B.push_back(A[j] - A[i]);
				minB = min(minB, B.back());
				if (AM.count(B.back()) > 0) {
					twoStep = true;
				}
			}
		}
		if (twoStep && K >= 2) {
			cout << 0 << '\n';
			continue;
		}
		if (K == 1) {
			cout << min(minB, A[0]) << '\n';
			continue;
		}
		sort(B.begin(), B.end());
		LL Z{min(A[0], minB)};
		RF(i, 0, N) {
			auto it = lower_bound(B.begin(), B.end(), A[i]);
			if (it != B.end()) {
				Z = min(Z, *it - A[i]);
			}
			if (it != B.begin()) {
				it--;
				Z = min(Z, A[i] - *it);
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
