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
		LL N, A, B;
		cin >> N >> A >> B;
		if (A == 0 && B != 0 || A != 0 && B == 0 || A + B > N) {
			cout << "NO\n";
			continue;
		}
		cout << "YES\n";
		if (A == 0) {
			RF(i, 0, 2) {
				RF(j, 1, N + 1) {
					cout << j << ' ';
				}
				cout << '\n';
			}
			continue;
		}
		LL C{A + B};
		vector<pair<LL, LL>> Z;
		RF(i, C, C - A) {
			Z.push_back({i, i - B});
		}
		RF(i, C, C - B) {
			Z.push_back({i - A, i});
		}
		RF(i, C, N) {
			Z.push_back({i + 1, i + 1});
		}
		RF(j, 0, N) {
			cout << Z[j].first << ' ';
		}
		cout << '\n';
		RF(j, 0, N) {
			cout << Z[j].second << ' ';
		}
		cout << '\n';
	}

	return 0;
}
