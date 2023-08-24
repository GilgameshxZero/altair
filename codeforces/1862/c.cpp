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
		LL N;
		cin >> N;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		if (A[0] != N) {
			cout << "NO\n";
			continue;
		}

		vector<LL> B;
		A.push_back(0);
		RF(i, N - 1, -1) {
			RF(j, 0, A[i] - A[i + 1]) {
				B.push_back(i + 1);
			}
		}
		A.pop_back();

		cout << (A == B ? "YES" : "NO") << '\n';
	}

	return 0;
}
