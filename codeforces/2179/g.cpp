#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N;
		cin >> N;
		vector<vector<LL>> CD1(N * 2 - 1);
		RF(i, 2, N * N + 1) {
			cout << "? " << 1 << ' ' << i << endl;
			LL X;
			cin >> X;
			CD1[X].push_back(i);
		}
		while (CD1.back().empty()) {
			CD1.pop_back();
		}
		vector<LL> CADJ;
		vector<array<LL, 2>> D(N * N + 1);
		if (CD1.back().size() == 1) {
			CADJ.push_back(CD1.back()[0]);
		} else if (CD1.back().size() == 4) {
			CADJ.push_back(CD1.back()[0]);
			RF(i, 1, 4) {
				cout << "? " << CD1.back()[0] << ' '
						 << CD1.back()[i] << endl;
				LL X;
				cin >> X;
				if (X == N - 1) {
					CADJ.push_back(CD1.back()[i]);
					break;
				}
			}
		} else {
			CADJ = CD1.back();
		}
		RF(i, 1, N * N + 1) {
			cout << "? " << CADJ[0] << ' ' << i << endl;
			cin >> D[i][0];
		}
		if (CADJ.size() == 1) {
			vector<LL> CRIT;
			RF(i, 1, N * N + 1) {
				if (D[i][0] == N - 1) {
					CRIT.push_back(i);
				}
			}
			vector<vector<LL>> CDCRIT(N * 2 - 1);
			RF(i, 1, CRIT.size()) {
				cout << "? " << CRIT[0] << ' ' << CRIT[i] << endl;
				LL X;
				cin >> X;
				CDCRIT[X].push_back(CRIT[i]);
			}
			while (CDCRIT.back().empty()) {
				CDCRIT.pop_back();
			}
			CADJ.push_back(CDCRIT.back()[0]);
		}
		RF(i, 1, N * N + 1) {
			cout << "? " << CADJ[1] << ' ' << i << endl;
			cin >> D[i][1];
		}
		vector<vector<LL>> Z(N, vector<LL>(N));
		RF(i, 1, N * N + 1) {
			LL LE{N - 1};
			LE += D[i][0];
			LL C{(LE - D[i][1]) / 2}, R{D[i][0] - C};
			Z[R][C] = i;
		}
		cout << "!\n";
		RF(i, 0, N) {
			RF(j, 0, N) {
				cout << Z[i][j] << ' ';
			}
			cout << '\n';
		}
		cout << endl;
	}

	return 0;
}
