#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, f, t)                                      \
	for (LL x(f), _t(t), _d{x < _t ? 1LL : -1LL}; x != _t; \
			 x += _d)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		string X;
		cin >> X;
		if (X[0] != '1' || X.back() == '9') {
			cout << "NO\n";
			continue;
		}
		X.pop_back();
		sort(X.begin(), X.end());
		if (X[0] == '0') {
			cout << "NO\n";
			continue;
		}
		cout << "YES\n";
	}

	return 0;
}
