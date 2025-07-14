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

	LL N, A, B;
	cin >> N >> A >> B;
	map<LL, LL> C;
	RF(i, 0, N) {
		LL x;
		cin >> x;
		C[x % (A + B)]++;
	}
	auto i{C.begin()};
	LL D{0}, c{0};
	for (auto j{C.begin()}; j != C.end(); j++) {
		while (i == C.end() || i->first + c <= j->first + B) {
			if (i == C.end()) {
				i = C.begin();
				c += A + B;
				continue;
			}
			D += i->second;
			i++;
		}
		D -= j->second;
		if (D == 0) {
			cout << "Yes";
			return 0;
		}
	}
	cout << "No";
	return 0;
}
