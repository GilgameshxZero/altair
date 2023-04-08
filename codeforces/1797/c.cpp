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
		LL N, M, A, B{LLONG_MAX / 2}, C{LLONG_MAX / 2};
		cin >> N >> M;
		cout << "? 1 1" << endl;
		cin >> A;
		if (A + 1 <= N) {
			cout << "? " << A + 1 << " 1" << endl;
			cin >> B;
		}
		if (A + 1 <= M) {
			cout << "? 1 " << A + 1 << endl;
			cin >> C;
		}
		if (B >= A && C >= A) {
			cout << "! " << A + 1 << ' ' << A + 1 << endl;
		} else if (B >= A) {
			cout << "! " << C + 1 << ' ' << A + 1 << endl;
		} else {
			cout << "! " << A + 1 << ' ' << B + 1 << endl;
		}
	}

	return 0;
}
