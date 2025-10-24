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
		LL N, Q;
		cin >> N >> Q;
		string S;
		cin >> S;
		bool A{false};
		{
			string SS{S};
			sort(SS.begin(), SS.end());
			if (SS.back() == 'A') {
				A = true;
			}
		}
		RF(i, 0, Q) {
			LL B;
			cin >> B;
			if (A) {
				cout << B << '\n';
				continue;
			}
			LL Z{0};
			for (LL j{0}; B > 0; j = (j + 1) % N, Z++) {
				if (S[j] == 'A') {
					B--;
				} else {
					B /= 2;
				}
			}
			cout << Z << '\n';
		}
	}

	return 0;
}
