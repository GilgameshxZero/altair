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
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}

		vector<pair<LL, LL>> Z;
			LL iLow{0}, iHigh{0};
			RF(i, 0, N) {
				if (A[i] < A[iLow]) {
					iLow = i;
				}
				if (A[i] > A[iHigh]) {
					iHigh = i;
				}
			}
			if (A[iLow] == 0 && A[iHigh] == 0) {
				} else if (A[iLow] < 0 && A[0] + A[iLow] <= 0) {

			} else if ()
		if (high == 0) {
			Z.push_back({0, iLow});
			RF(i, N - 1, 0) {
				Z.push_back({i, 0});
				Z.push_back({0, 0});
			}
		} else {
			RF(i, 0, N) {
				Z.push_back({i, iHigh});
				Z.push_back({iHigh, iHigh});
			}
		}
		cout << Z.size() << '\n';
		RF(i, 0, Z.size()) {
			cout << Z[i].first + 1 << ' ' << Z[i].second + 1 << '\n';
		}
	}

	return 0;
}
