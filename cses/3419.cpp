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

	array<set<LL>, 100> C, R;
	RF(i, 0, 100) {
		RF(j, 0, 500) {
			C[i].insert(j);
		}
	}

	LL N;
	cin >> N;
	RF(i, 0, N) {
		RF(j, 0, N) {
			auto k{C[j].begin()};
			while (R[i].count(*k)) {
				k++;
			}
			cout << *k << ' ';
			R[i].insert(*k);
			C[j].erase(k);
		}
		cout << '\n';
	}

	return 0;
}
