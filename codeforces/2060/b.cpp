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
		LL N, M;
		cin >> N >> M;
		vector<pair<vector<LL>, LL>> A(N);
		RF(i, 0, N) {
			A[i].first.resize(M);
			A[i].second = i;
			RF(j, 0, M) {
				cin >> A[i].first[j];
			}
			sort(A[i].first.begin(), A[i].first.end());
		}
		sort(
			A.begin(), A.end(), [](pair<vector<LL>, LL> &X, pair<vector<LL>, LL> &Y) {
				return X.first[0] < Y.first[0];
			});
		bool fail{false};
		RF(i, 0, N) {
			RF(j, 0, M) {
				if (A[i].first[j] != i + j * N) {
					fail = true;
					break;
				}
			}
			if (fail) {
				break;
			}
		}
		if (fail) {
			cout << -1 << '\n';
		} else {
			RF(i, 0, N) {
				cout << A[i].second + 1 << ' ';
			}
			cout << '\n';
		}
	}

	return 0;
}
