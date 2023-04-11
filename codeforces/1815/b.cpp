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
		cout << "+ " << N << "\n+ " << N + 1 << '\n';
		RF(i, 1, N) {
			cout << "? 1 " << i + 1 << '\n';
		}
		LL t, amax, mmax{0};
		cout.flush();
		cin >> t >> t;
		RF(i, 1, N) {
			cin >> t;
			if (t > mmax) {
				mmax = t;
				amax = i;
			}
		}

		vector<pair<LL, LL>> lto(N);
		lto[amax] = {0, amax};
		RF(i, 0, N) {
			if (i == amax) {
				continue;
			}
			cout << "? " << amax + 1 << ' ' << i + 1 << endl;
			cin >> t;
			lto[i] = {t, i};
		}
		sort(lto.begin(), lto.end());

		vector<LL> cand[2];
		cand[0].resize(N);
		cand[1].resize(N);
		LL cur{N - 1}, delta{-(N - 1)};
		RF(i, 0, N) {
			cand[0][i] = cur;
			cur += delta;
			delta = -delta;
			delta += (delta > 0 ? -1 : 1);
		}
		cand[1] = cand[0];
		reverse(cand[1].begin(), cand[1].end());

		vector<LL> ans[2];
		ans[0].resize(N);
		ans[1].resize(N);
		RF(i, 0, N) {
			ans[0][lto[i].second] = cand[0][i];
			ans[1][lto[i].second] = cand[1][i];
		}

		cout << "!";
		RF(i, 0, 2) {
			RF(j, 0, N) {
				cout << ' ' << ans[i][j] + 1;
			}
		}
		cout << endl;
		cin >> t;
	}

	return 0;
}
