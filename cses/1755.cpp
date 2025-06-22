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

	string S;
	cin >> S;
	map<char, int> F;
	RF(i, 0, S.length()) {
		F[S[i]]++;
	}
	string Z, Y;
	for (auto i : F) {
		while (i.second >= 2) {
			i.second -= 2;
			Z += i.first;
		}
		if (i.second == 1) {
			Y += i.first;
		}
	}
	if (Y.length() > 1) {
		cout << "NO SOLUTION";
		return 0;
	}
	cout << Z << Y;
	reverse(Z.begin(), Z.end());
	cout << Z;

	return 0;
}
