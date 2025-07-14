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

	string S;
	cin >> S;
	if (S[0] != '<' || S.back() != '>') {
		cout << "No";
	} else {
		S.erase(S.begin());
		S.erase(prev(S.end()));
		if (S == string(S.size(), '=')) {
			cout << "Yes";
		} else {
			cout << "No";
		}
	}

	return 0;
}
