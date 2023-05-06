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

	LL N, M;
	cin >> M >> N;
	vector<LL> P(N);
	RF(i, 0, N) {
		cin >> P[i];
	}

	vector<bitset<5000>> E(N);
	RF(i, 0, N) {
		E[i].set();
	}
	vector<pair<LL, LL>> X(N);
	RF(i, 0, M) {
		RF(i, 0, N) {
			cin >> X[i].first;
			X[i].second = i;
		}
		sort(X.begin(), X.end());

		bitset<5000> Y;
		RF(i, 0, N) {
			E[X[i].second] &= Y;
			if (i < N - 1 && X[i].first < X[i + 1].first) {
				RF(j, i, -1) {
					if (Y.test(X[j].second)) {
						break;
					}
					Y.set(X[j].second);
				}
			}
		}
	}

	vector<LL> B(N);
	B[X[0].second] = P[X[0].second];
	LL Z{B[X[0].second]};
	RF(i, 1, N) {
		B[X[i].second] = P[X[i].second];
		RF(j, 0, i) {
			if (E[X[i].second].test(X[j].second)) {
				B[X[i].second] = max(B[X[i].second], P[X[i].second] + B[X[j].second]);
			}
		}
		Z = max(Z, B[X[i].second]);
	}
	cout << Z << '\n';

	return 0;
}
