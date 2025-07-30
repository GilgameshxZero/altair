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

	string S, T;
	cin >> S >> T;
	if (S.length() < T.length()) {
		swap(S, T);
	}

	vector<LL> Y(T.length() + 1);
	Y[1] = S.back() == T.back() ? 0 : 1;
	RF(i, 2, T.length() + 1) {
		Y[i] = Y[i - 1] + (S[S.length() - i] == T[T.length() - i] ? 0 : 1);
	}
	RF(i, 1, S.length() - T.length() + 1) {
		vector<LL> X(T.length() + 1);
		X[1] =
			min(1 + Y[1], S[S.length() - 1 - i] == T[T.length() - 1] ? i : i + 1);
		RF(j, 2, T.length() + 1) {
			X[j] = min(1 + Y[j],
				(S[S.length() - j - i] == T[T.length() - j] ? 0 : 1) + X[j - 1]);
		}
		swap(X, Y);
	}
	cout << Y[T.length()] << '\n';

	return 0;
}
