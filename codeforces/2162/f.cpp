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
		vector<pair<LL, LL>> A(M);
		pair<LL, LL> O{LLONG_MIN, LLONG_MAX};
		vector<bool> B(N), E(N);
		RF(i, 0, M) {
			cin >> A[i].first >> A[i].second;
			A[i].first--;
			A[i].second--;
			O.first = max(O.first, A[i].first);
			O.second = min(O.second, A[i].second);
			B[A[i].first] = true;
			E[A[i].second] = true;
		}
		if (O.first <= O.second) {
			RF(i, 0, O.first) {
				cout << i + 1 << ' ';
			}
			cout << 0 << ' ';
			RF(i, O.first + 1, N) {
				cout << i << ' ';
			}
			cout << '\n';
			continue;
		}

		bool fail{true};
		RF(i, 0, N - 1) {
			if (!(E[i] && B[i + 1])) {
				vector<LL> Z(N);
				if (E[i]) {
					Z[i] = 1;
				} else {
					Z[i] = 0;
				}
				Z[i + 1] = 1 - Z[i];
				RF(j, 0, i) {
					Z[j] = 2 + j;
				}
				RF(j, i + 2, N) {
					Z[j] = j;
				}
				RF(j, 0, N) {
					cout << Z[j] << ' ';
				}
				cout << '\n';
				fail = false;
				break;
			}
		}
		if (!fail) {
			continue;
		}

		cout << "0 2 1 ";
		RF(i, 3, N) {
			cout << i << ' ';
		}
		cout << '\n';
	}

	return 0;
}
