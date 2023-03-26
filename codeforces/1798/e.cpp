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

#pragma hdrstop	 // ------------------------------------------------------------

int main(int, char const *[]) {
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
		vector<LL> Ts(N);
		Ts.back() = -1;
		RF(i, N - 2, -1) {
			LL crit{i + 1 + A[i]};
			if (crit == N) {
				Ts[i] = 1;
			} else if (crit > N) {
				Ts[i] = -1;
			} else if (Ts[crit] == -1) {
				Ts[i] = -1;
			} else {
				Ts[i] = 1 + Ts[crit];
			}
		}
		vector<LL> pmts(N);
		pmts.back() = Ts.back();
		RF(i, N - 2, -1) {
			pmts[i] = max(pmts[i + 1], Ts[i]);
		}
		vector<LL> m1rt(N);
		m1rt.back() = 1;
		RF(i, N - 2, -1) {
			LL crit{i + 1 + A[i]};
			if (crit > N) {
				m1rt[i] = max(1LL, 1 + pmts[i + 1]);
			} else if (crit == N) {
				m1rt[i] = max(1LL, 1 + pmts[i + 1]);
			} else {
				m1rt[i] = max(1 + m1rt[crit], 1 + pmts[i + 1]);
			}
		}

		RF(i, 0, N - 1) {
			if (Ts[i + 1] == A[i]) {
				cout << 0 << ' ';
				continue;
			}
			if (Ts[i + 1] != -1) {
				cout << 1 << ' ';
				continue;
			}
			if (m1rt[i + 1] >= A[i]) {
				cout << 1 << ' ';
				continue;
			}
			cout << 2 << ' ';
		}
		cout << '\n';
	}

	return 0;
}
