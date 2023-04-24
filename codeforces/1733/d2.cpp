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
		LL N, X, Y;
		string A, B;
		cin >> N >> X >> Y >> A >> B;

		vector<LL> P;
		RF(i, 0, N) {
			if (A[i] != B[i]) {
				P.push_back(i);
			}
		}
		if (P.size() % 2 != 0) {
			cout << "-1\n";
			continue;
		}
		if (P.empty()) {
			cout << "0\n";
			continue;
		}
		if (X >= Y) {
			if (P.size() == 2) {
				if (P[0] + 1 == P[1]) {
					if (X < Y * 2) {
						cout << X << '\n';
					} else {
						cout << Y * 2 << '\n';
					}
				} else {
					cout << Y << '\n';
				}
			} else {
				cout << Y * P.size() / 2 << '\n';
			}
			continue;
		}

		vector<pair<LL, LL>> I;
		I.push_back({P[0], P[0]});
		RF(i, 1, P.size()) {
			if (P[i] == I.back().second + 1) {
				I.back().second++;
			} else {
				I.push_back({P[i], P[i]});
			}
		}

		vector<LL> IO;
		LL C0{0};
		RF(i, 0, I.size()) {
			C0 += (I[i].second - I[i].first + 1) / 2;
			if ((I[i].second - I[i].first + 1) % 2 == 1) {
				IO.push_back(i);
			}
		}
		if (IO.empty()) {
			cout << C0 * X << '\n';
			continue;
		}

		vector<LL> O(IO.size() - 1);
		RF(i, 0, IO.size() - 1) {
			O[i] = I[IO[i + 1]].first - I[IO[i]].second - 1;
			RF(j, IO[i] + 1, IO[i + 1]) {
				O[i] -= I[j].second - I[j].first + 1;
			}
		}

		vector<vector<LL>> BF(
			O.size() + 1, vector<LL>(O.size() + 2, LLONG_MAX / 2));
		BF[0][1] = 0;
		BF[1][0] = O[0] + 1;
		BF[1][2] = 0;
		RF(i, 2, BF.size()) {
			BF[i][0] = BF[i - 2][0] + O[i - 1] + 1;
			RF(j, 1, BF[i].size()) {
				BF[i][j] = min(BF[i - 1][j - 1], BF[i - 2][j] + O[i - 1] + 1);
			}
		}

		LL vmin{LLONG_MAX / 2}, amin;
		RF(i, 0, BF.back().size()) {
			if (BF.back()[i] >= LLONG_MAX / 2) {
				continue;
			}
			if (BF.back()[i] * X + Y * i / 2 < vmin) {
				vmin = BF.back()[i] * X + Y * i / 2;
				amin = i;
			}
		}

		cout << C0 * X + vmin << '\n';
	}

	return 0;
}
