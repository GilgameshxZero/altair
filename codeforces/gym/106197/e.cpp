#if defined(__GNUC__) && !defined(__clang__) && !defined(__MINGW32__)
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

	LL N, L{3};
	string S, T;
	cin >> N >> S;
	vector<LL> X;
	vector<bool> OT, OB;
	map<pair<LL, LL>, char> Z;
	RF(i, 0, N) {
		RF(j, 0, X.size()) {
			if (S[X[j]] != S[i]) {
				continue;
			}

			if (j == 2) {
				// Do nothing.
			} else if (j == 1) {
				if (OT[j]) {
					OT[j] = OT[j + 1] = false;
					RF(k, X[j], i + 1) {
						Z[{k, 1}] = S[i];
					}
				} else {
					OB[j] = OB[j + 1] = false;
					RF(k, X[j], i + 1) {
						Z[{k, -1}] = S[i];
					}
				}
			} else if (j == 0) {
				if (OT[j]) {
					if (OB[j + 1]) {
						OT[j] = OT[j + 1] = OT[j + 2] = false;
						Z[{X[j], 1}] = Z[{i, 1}] = S[i];
						RF(k, X[j], i + 1) {
							Z[{k, 2}] = S[i];
						}
					} else {
						OT[j] = OB[j] = OB[j + 1] = OB[j + 2] = false;
						RF(k, 1, L + 1) {
							Z[{X[j], k}] = Z[{-k, L}] = Z[{-L, k}] = Z[{-L, -k}] =
								Z[{-k, -L}] = Z[{i, -k}] = S[i];
						}
						Z[{-L, 0}] = S[i];
						RF(k, 0, X[j]) {
							Z[{k, L}] = Z[{k, -L}] = S[i];
						}
						RF(k, X[j], i + 1) {
							Z[{k, -L}] = S[i];
						}
						L++;
					}
				} else {
					if (OT[j + 1]) {
						OB[j] = OB[j + 1] = OB[j + 2] = false;
						Z[{X[j], -1}] = Z[{i, -1}] = S[i];
						RF(k, X[j], i + 1) {
							Z[{k, -2}] = S[i];
						}
					} else {
						OB[j] = OT[j] = OT[j + 1] = OT[j + 2] = false;
						RF(k, 1, L + 1) {
							Z[{X[j], -k}] = Z[{-k, -L}] = Z[{-L, -k}] = Z[{-L, k}] =
								Z[{-k, L}] = Z[{i, k}] = S[i];
						}
						Z[{-L, 0}] = S[i];
						RF(k, 0, X[j]) {
							Z[{k, L}] = Z[{k, -L}] = S[i];
						}
						RF(k, X[j], i + 1) {
							Z[{k, L}] = S[i];
						}
						L++;
					}
				}
			}

			X.erase(X.begin() + j);
			OT.erase(OT.begin() + j);
			OB.erase(OB.begin() + j);
			break;
		}
		X.push_back(i);
		OT.push_back(true);
		OB.push_back(true);
	}

	RF(i, 0, N) {
		Z.erase({i, 0});
	}
	cout << Z.size() << '\n';
	for (auto &i : Z) {
		cout << i.first.first << ' ' << i.first.second << ' ' << i.second << '\n';
	}

	return 0;
}
