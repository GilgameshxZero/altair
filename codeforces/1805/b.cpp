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
		string S;
		cin >> S;
		if (N == 1) {
			cout << S << '\n';
			continue;
		}
		string T{S};
		sort(T.begin() + 1, T.end());
		if (T[1] > S[0]) {
			cout << S << '\n';
		} else {
			auto i{S.find_last_of(T[1])};
			cout << S[i] << S.substr(0, i) << S.substr(i + 1) << '\n';
		}
	}

	return 0;
}
