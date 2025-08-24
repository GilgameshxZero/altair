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
		vector<vector<LL>> D(N + 1);
		RF(i, 0, N) {
			cout << "? " << i + 1 << ' ' << N << ' ';
			RF(j, 0, N) {
				cout << j + 1 << ' ';
			}
			cout << endl;
			LL d;
			cin >> d;
			D[d].push_back(i);
		}
		while (D.back().empty()) {
			D.pop_back();
		}

		LL R{N}, Y(D.size() - 1);
		RF(i, 1, D.size() - 1) {
			RF(j, 0, D[i].size()) {
				cout << "? " << D.back()[0] + 1 << ' ' << R + 1 - D[i].size() << ' ';
				cout << D[i][j] + 1 << ' ';
				RF(k, 1, D.size()) {
					if (k == i) {
						continue;
					}
					RF(l, 0, D[k].size()) {
						cout << D[k][l] + 1 << ' ';
					}
				}
				cout << endl;
				LL d;
				cin >> d;
				if (d == Y) {
					R -= D[i].size();
					R++;
					LL z{D[i][j]};
					D[i].clear();
					D[i].push_back(z);
					break;
				}
			}
		}

		LL z{D.back()[0]};
		D.back().clear();
		D.back().push_back(z);

		cout << "! " << Y << ' ';
		RF(i, D.size() - 1, 0) {
			cout << D[i][0] + 1 << ' ';
		}
		cout << endl;
	}

	return 0;
}
