#if defined(__GNUC__) && !defined(__clang__)
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

	LL T;
	cin >> T;
	while (T--) {
		LL N, K;
		cin >> N;
		vector<pair<LL, LL>> S;
		RF(i, 0, N) {
			LL c;
			cin >> c;
			while (!S.empty() && S.back().first >= c) {
				S.pop_back();
			}
			S.push_back({c, i});
		}
		cin >> K;
		LL C{0}, A{LLONG_MAX / 2};
		vector<LL> Z(N, -1);
		RF(i, 0, S.size()) {
			LL D{K / (S[i].first - C)};
			D = min(D, A);
			K -= D * (S[i].first - C);
			Z[S[i].second] = D;
			A = D;
			C = S[i].first;
		}
		vector<LL> Y(N);
		Y.back() = Z.back();
		RF(i, N - 2, -1) {
			Y[i] = Z[i] == -1 ? Y[i + 1] : Z[i];
		}
		RF(i, 0, N) {
			cout << Y[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
