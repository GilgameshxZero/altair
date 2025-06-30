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

	LL N;
	cin >> N;

	set<LL> S;
	RF(i, 0, N) {
		S.insert(i + 1);
	}
	auto i{S.begin()};
	while (!S.empty()) {
		i++;
		if (i == S.end()) {
			i = S.begin();
		}
		cout << *i << ' ';
		i = S.erase(i);
		if (i == S.end()) {
			i = S.begin();
		}
	}

	return 0;
}
