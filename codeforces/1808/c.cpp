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

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL L, R;
		cin >> L >> R;
		// if (L == R) {
		// 	cout << L << '\n';
		// 	continue;
		// }

		bool done{false};
		RF(i, 0, 10) {
			RF(j, 0, 9 - i + 1) {
				LL l{j}, r{j + i};
				array<string, 4> possible;
				possible.fill("");
				possible[0] = "0";

				LL div{1000000000000000000};
				bool leading{true};
				RF(k, 18, -1) {
					LL Lk{L / div}, Rk{R / div};
					Lk %= 10;
					leading &= Lk == 0;
					Rk %= 10;
					div /= 10;
					decltype(possible) p2;
					p2.fill("");
					RF(n, 0, 4) {
						if (possible[n].empty()) {
							continue;
						}
						bool psR{(n / 2) == 1}, plL{(n % 2) == 1};
						LL ll{l}, rr{r};
						if (!psR) {
							rr = min(rr, Rk);
						}
						if (!plL) {
							ll = max(ll, Lk);
						}
						for (LL m{ll}; m <= rr; m++) {
							LL l2{n};
							l2 |= (m < Rk) << 1;
							l2 |= (m > Lk);
							p2[l2] = possible[n] + (char)(m + '0');
						}
						if (possible[n] == "0" && leading) {
							LL l2{n};
							l2 |= (0 < Rk) << 1;
							l2 |= (0 > Lk);
							p2[l2] = "0";
						}
					}
					p2.swap(possible);
				}

				for (auto &p : possible) {
					if (!p.empty()) {
						cout << p.substr(1) << '\n';
						done = true;
						break;
					}
				}
				if (done) {
					break;
				}
			}
			if (done) {
				break;
			}
		}
	}

	return 0;
}
