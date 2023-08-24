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
		LL N, M, D;
		cin >> N >> M >> D;

		priority_queue<LL, vector<LL>, greater<LL>> P;
		LL S{0}, Z{0};
		RF(i, 0, N) {
			LL x;
			cin >> x;
			if (x > 0) {
				P.push(x);
				S += x;
				if (P.size() > M) {
					S -= P.top();
					P.pop();
				}
				Z = max(Z, S - D * (i + 1));
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
