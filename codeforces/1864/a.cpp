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
		LL A, B, N;
		cin >> A >> B >> N;
		vector<LL> C(N);
		C[N - 1] = B;
		LL D{1};
		RF(i, N - 2, -1) {
			C[i] = C[i + 1] - D++;
		}
		if (C[0] >= A) {
			C[0] = A;
			RF(i, 0, N) {
				cout << C[i] << ' ';
			}
			cout << '\n';
		} else {
			cout << -1 << '\n';
		}
	}

	return 0;
}
