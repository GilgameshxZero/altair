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

	// LL X{100000}, C{0};
	// while (X >= 4) {
	// 	X = 3 * (X / 4) + (X % 4);
	// 	C++;
	// }
	// cout << C;  // 38.
	// return 0;

	LL N;
	cin >> N;
	vector<LL> P;
	RF(i, 1, N + 1) {
		P.push_back(i);
	}
	while (P.size() >= 4) {
		LL B(P.size() / 4), D(P.size() % 4);
		vector<LL> Q[4];
		RF(i, 0, 4) {
			RF(j, 0, B) {
				Q[i].push_back(P.back());
				P.pop_back();
			}
			if (i < D) {
				Q[i].push_back(P.back());
				P.pop_back();
			}
		}

		cout << "? " << Q[0].size() + Q[1].size();
		for (auto &i : {0, 1}) {
			RF(j, 0, Q[i].size()) {
				cout << ' ' << Q[i][j];
			}
		}
		cout << "\n? " << Q[1].size() + Q[2].size();
		for (auto &i : {1, 2}) {
			RF(j, 0, Q[i].size()) {
				cout << ' ' << Q[i][j];
			}
		}
		cout << endl;

		string A[2];
		cin >> A[0] >> A[1];
		if (A[0] == "YES") {
			if (A[1] == "YES") {
				for (auto &i : {0, 1, 2}) {
					RF(j, 0, Q[i].size()) {
						P.push_back(Q[i][j]);
					}
				}
			} else {
				for (auto &i : {0, 1, 3}) {
					RF(j, 0, Q[i].size()) {
						P.push_back(Q[i][j]);
					}
				}
			}
		} else {
			if (A[1] == "YES") {
				for (auto &i : {1, 2, 3}) {
					RF(j, 0, Q[i].size()) {
						P.push_back(Q[i][j]);
					}
				}
			} else {
				for (auto &i : {0, 2, 3}) {
					RF(j, 0, Q[i].size()) {
						P.push_back(Q[i][j]);
					}
				}
			}
		}
	}

	if (P.size() == 3) {
		cout << "? 1 " << P[0] << endl;
		string A;
		cin >> A;
		if (A == "YES") {
			cout << "! " << P[0] << endl;
			cin >> A;
			if (A != ":)") {
				cout << "? 1 " << P[1] << endl;
				cin >> A;
				if (A == "YES") {
					cout << "! " << P[1] << endl;
				} else {
					cout << "! " << P[2] << endl;
				}
			}
		} else {
			cout << "? 1 " << P[0] << endl;
			cin >> A;
			if (A == "YES") {
				cout << "! " << P[0] << endl;
				cin >> A;
				if (A != ":)") {
					cout << "? 1 " << P[1] << endl;
					cin >> A;
					if (A == "YES") {
						cout << "! " << P[1] << endl;
					} else {
						cout << "! " << P[2] << endl;
					}
				}
			} else {
				cout << "! " << P[0] << endl;
			}
		}
		return 0;
	}

	RF(i, 0, P.size()) {
		cout << "! " << P[i] << endl;
		string A;
		cin >> A;
		if (A == ":)") {
			break;
		}
	}

	return 0;
}
