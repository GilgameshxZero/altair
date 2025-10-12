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

		vector<LL> Z(2 * N);
		vector<LL> S[2];
		S[0].push_back(0);
		RF(i, 1, 2 * N) {
			cout << "? " << S[0].size() + 1 << ' ';
			RF(j, 0, S[0].size()) {
				cout << S[0][j] + 1 << ' ';
			}
			cout << i + 1 << endl;
			LL z;
			cin >> z;
			if (z == 0) {
				S[0].push_back(i);
			} else {
				S[1].push_back(i);
				Z[i] = z;
			}
		}

		RF(i, 0, 1) {
			RF(j, 0, S[i].size()) {
				cout << "? " << S[1 - i].size() + 1 << ' ';
				RF(k, 0, S[1 - i].size()) {
					cout << S[1 - i][k] + 1 << ' ';
				}
				cout << S[i][j] + 1 << endl;
				cin >> Z[S[i][j]];
			}
		}

		cout << "! ";
		RF(i, 0, 2 * N) {
			cout << Z[i] << ' ';
		}
		cout << endl;
	}

	return 0;
}
