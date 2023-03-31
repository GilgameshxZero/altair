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

	unordered_set<LL> us;

	LL T;
	cin >> T;
	while (T--) {
		LL Q;
		cin >> Q;

		LL hl{1}, hh{LLONG_MAX / 2};
		RF(i, 0, Q) {
			LL TT;
			cin >> TT;
			if (TT == 1) {
				LL A, B, N;
				cin >> A >> B >> N;

				LL ul, uh;
				if (N == 1) {
					ul = 1;
					uh = A;
				} else {
					ul = (N - 1) * (A - B) + B + 1;
					uh = (N - 1) * (A - B) + A;
				}

				if (ul > hh || uh < hl) {
					cout << "0 ";
				} else {
					cout << "1 ";
					hl = max(hl, ul);
					hh = min(hh, uh);
				}
			} else {
				LL A, B;
				cin >> A >> B;

				us.clear();
				if (A >= hl) {
					us.insert(1);
				}
				LL cand{(hl - A + (A - B - 1)) / (A - B) + 1};
				if (cand >= 2 && (cand - 1) * (A - B) + B + 1 <= hl) {
					us.insert(cand);
				}
				cand = (hh - A + (A - B - 1)) / (A - B) + 1;
				if (cand >= 2 && (cand - 1) * (A - B) + B + 1 <= hh) {
					us.insert(cand);
				}

				if (us.size() == 1) {
					cout << *us.begin() << ' ';
				} else {
					cout << "-1 ";
				}
			}
		}

		cout << '\n';
	}

	return 0;
}
