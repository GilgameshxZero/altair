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
		LL N, M;
		cin >> N >> M;
		vector<LL> A(N), B(N), _PA(N + 1), _PB(N + 1);
		LL *PA{_PA.data() + 1}, *PB{_PB.data() + 1};
		RF(i, 0, N) {
			cin >> A[i];
			PA[i] = PA[i - 1] + A[i];
		}
		RF(i, 0, N) {
			cin >> B[i];
			PB[i] = PB[i - 1] + B[i];
		}
		vector<vector<LL>> II(N);
		RF(i, 0, M) {
			LL X, Y;
			cin >> X >> Y;
			II[Y - 1].push_back(X - 1);
		}

		unordered_set<LL> S;
		S.insert(PA[N - 1]);
		RF(i, 0, N) {
			for (auto &j : II[i]) {
				LL target{PB[i] - PB[j - 1]};
			}
		}
	}

	return 0;
}
