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
		string S;
		cin >> S;
		bool A[10]{false};
		RF(i, 0, 9) {
			if (S[i] == '1' && A[3]) {
				cout << "31\n";
				break;
			} else if (S[i] == '3' && A[1]) {
				cout << "13\n";
				break;
			}
			A[S[i] - '0'] = true;
		}
	}

	return 0;
}
