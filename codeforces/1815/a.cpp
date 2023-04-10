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
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		if (N % 2 == 1) {
			cout << "YES\n";
			continue;
		}
		LL carry{0};
		for (LL i{0}; i < N - 1; i += 2) {
			carry = A[i] + carry - A[i + 1];
		}
		cout << (carry <= 0 ? "YES" : "NO") << '\n';
	}

	return 0;
}
