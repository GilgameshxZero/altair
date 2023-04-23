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

		vector<LL> A(N), B(N);
		unordered_map<LL, vector<LL>> pB;
		RF(i, 0, N) {
			cin >> B[i];
			pB[B[i]].push_back(i);
		}
		LL I{0};
		if (B[0] == N + 1) {
			while (B[I] == N + 1) {
				A[I] = I + 1;
				I++;
			}
		} else {
			while (B[N - 1 - I] == 0) {
				A[I] = N - I;
				I++;
			}
		}
	}

	return 0;
}
