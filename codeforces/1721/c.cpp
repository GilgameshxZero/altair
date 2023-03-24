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

#pragma hdrstop	 // ------------------------------------------------------------

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> A(N), B(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		RF(i, 0, N) {
			cin >> B[i];
		}

		vector<LL> maxAns(N), minAns(N);
		LL p2{0};
		RF(i, 0, N) {
			while (p2 < N && B[p2] < A[i]) {
				p2++;
			}
			minAns[i] = B[p2] - A[i];
		}

		multiset<LL> rB;
		RF(i, 0, N) {
			rB.insert(B[i]);
		}
		RF(i, N - 1, -1) {
			maxAns[i] = *rB.rbegin() - A[i];
			rB.erase(rB.lower_bound(A[i]));
		}

		RF(i, 0, N) {
			cout << minAns[i] << ' ';
		}
		cout << '\n';
		RF(i, 0, N) {
			cout << maxAns[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
