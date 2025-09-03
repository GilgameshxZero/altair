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
		LL t, N;
		cin >> t >> N;
		if (t == 1) {
			LL k;
			cin >> k;
			LL F{1};
			vector<LL> X(N);
			RF(i, 0, N) {
				X[i] = i + 1;
				F *= i + 1;
			}
			k--;
			F /= N;
			RF(i, 0, N) {
				LL c{k / F};
				k %= F;
				if (i < N - 1) {
					F /= (N - i - 1);
				}
				cout << X[c] << ' ';
				X.erase(X.begin() + c);
			}
			cout << '\n';
		} else {
			vector<LL> k(N);
			RF(i, 0, N) {
				cin >> k[i];
			}
			LL F{1};
			vector<LL> X(N);
			RF(i, 0, N) {
				X[i] = i + 1;
				F *= i + 1;
			}
			LL Z{0};
			F /= N;
			RF(i, 0, N) {
				RF(j, 0, X.size()) {
					if (X[j] == k[i]) {
						X.erase(X.begin() + j);
						Z += F * j;
						if (i < N - 1) {
							F /= (N - i - 1);
						}
						break;
					}
				}
			}
			cout << Z + 1 << '\n';
		}
	}

	return 0;
}
