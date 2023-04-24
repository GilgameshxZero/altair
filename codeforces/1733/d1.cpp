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
	}

	return 0;
}
