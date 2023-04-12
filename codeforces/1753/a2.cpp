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
		LL N;
		cin >> N;
		vector<LL> A(N);
		LL S{0};
		RF(i, 0, N) {
			cin >> A[i];
			S += A[i];
		}
		LL target{(2 * (S > 0) - 1)}, tcnt{S / target / 2};
		if (abs(S) % 2 == 1) {
			cout << "-1\n";
			continue;
		}

		vector<bool> sign(N, true);
		if (S != 0) {
			vector<array<LL, 2>> chosen(N), choice(N);
			chosen[0] = {0, -LLONG_MAX / 2};
			RF(i, 1, N) {
				if (chosen[i - 1][0] >= chosen[i - 1][1]) {
					chosen[i][0] = chosen[i - 1][0];
					choice[i][0] = 0;
				} else {
					chosen[i][0] = chosen[i - 1][1];
					choice[i][0] = 1;
				}
				if (A[i] == target) {
					chosen[i][1] = chosen[i - 1][0] + 1;
					choice[i][1] = 0;
				} else {
					chosen[i][1] = -LLONG_MAX / 2;
					choice[i][1] = 1;
				}

				if (chosen[i][0] == tcnt || chosen[i][1] == tcnt) {
					LL cur{i}, cchoice;
					if (chosen[i][0] == tcnt) {
						cchoice = 0;
					} else {
						cchoice = 1;
					}

					while (cur > 0) {
						if (cchoice == 1) {
							sign[cur] = false;
						}
						cchoice = choice[cur][cchoice];
						cur--;
					}
					break;
				}
			}
		}

		LL cneg{0};
		RF(i, 0, N) {
			cneg += !sign[i];
		}
		cout << N - cneg << '\n';
		RF(i, 0, N - 1) {
			if (!sign[i]) {
				continue;
			}
			if (sign[i + 1]) {
				cout << i + 1 << ' ' << i + 1 << '\n';
			} else {
				cout << i + 1 << ' ' << i + 2 << '\n';
			}
		}
		if (sign.back()) {
			cout << N << ' ' << N << '\n';
		}
	}

	return 0;
}
