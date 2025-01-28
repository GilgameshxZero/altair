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
		vector<LL> A(4);
		RF(i, 0, 4) {
			cin >> A[i];
		}
		set<LL> S;
		S.insert(A[0] + A[1]);
		S.insert(A[2] - A[1]);
		S.insert(A[3] - A[2]);
		cout << 4 - S.size() << '\n';
	}

	return 0;
}
