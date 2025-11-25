#if defined(__GNUC__) && !defined(__clang__) && !defined(__MINGW32__)
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
		vector<LL> A(N), B(N + 1);
		RF(i, 0, N) {
			cin >> A[i];
			B[A[i]] = i;
		}
		bool fail{false};
		vector<vector<LL>> Z;
		RF(i, N, -1) {
			if (i == 0 || i % 4 == 3) {
				Z.push_back({});
				RF(j, 1, i + 1) {
					Z.back().push_back(B[j]);
				}
				break;
			}
			LL P{i - 1};
			if (A[P] == i) {
				continue;
			}
			Z.push_back({B[i], P});
			unordered_set<LL> S;
			S.insert(i);
			S.insert(A[P]);
			LL K{i ^ A[P]};
			RF(j, N, 0) {
				if (S.count(j)) {
					continue;
				}
				if (K <= N && S.count(K) == 0) {
					Z.back().push_back(B[K]);
					K = 0;
					break;
				}
				S.insert(j);
				Z.back().push_back(B[j]);
				K ^= j;
			}
			if (K != 0) {
				fail = true;
				break;
			}
			sort(Z.back().begin(), Z.back().end());
			vector<pair<LL, LL>> X;
			RF(j, 0, Z.back().size()) {
				X.push_back({A[Z.back()[j]], Z.back()[j]});
			}
			sort(X.begin(), X.end());
			RF(j, 0, X.size()) {
				A[Z.back()[j]] = X[j].first;
				B[X[j].first] = Z.back()[j];
			}
		}
		if (fail) {
			cout << "-1\n";
			continue;
		}
		cout << Z.size() << '\n';
		RF(i, 0, Z.size()) {
			cout << Z[i].size() << ' ';
			RF(j, 0, Z[i].size()) {
				cout << Z[i][j] + 1 << ' ';
			}
			cout << '\n';
		}
	}

	return 0;
}
