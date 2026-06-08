#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
	// <https://codeforces.com/blog/entry/135127>.
	#include <string>
	#pragma GCC target("arch=core-avx2")
	#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for ( \
		LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
		x != _to; \
		x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N;
		cin >> N;
		vector<LL> A(N), B(N), C(N);
		RF(i, 0, N) { cin >> A[i]; }
		set<LL> SB;
		RF(i, 0, N) {
			cin >> B[i];
			SB.insert(B[i]);
		}
		bool fail{false};
		RF(i, 0, N) {
			auto j{SB.lower_bound(A[i])};
			if (j == SB.end()) {
				fail = true;
				break;
			}
			C[i] = *j;
			SB.erase(j);
		}
		if (fail) {
			cout << "-1\n";
			continue;
		}
		// RF(i, 0, N) { cout << C[i] << ' '; }
		// cout << '\n';
		LL Z{};
		RF(i, 0, N) {
			RF(j, 0, i) { Z += C[j] > C[i]; }
		}
		cout << Z << '\n';
	}

	return 0;
}
