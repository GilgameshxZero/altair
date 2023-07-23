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
		LL N;
		cin >> N;
		multimap<LL, LL> A;
		RF(i, 0, N) {
			LL x;
			cin >> x;
			A.insert({x, i});
		}
		LL cp{0};
		vector<LL> Z(N);
		bool fail{false};
		RF(i, N, 0) {
			if (A.count(cp + i)) {
				auto j{A.find(cp + i)};
				Z[j->second] = i;
				A.erase(j);
				cp++;
			} else {
				auto j{A.find(cp)};
				if (j == A.end()) {
					fail = true;
					break;
				}
				Z[j->second] = -i;
				A.erase(j);
			}
		}
		if (fail) {
			cout << "NO\n";
		} else {
			cout << "YES\n";
			RF(i, 0, N) {
				cout << Z[i] << ' ';
			}
			cout << '\n';
		}
	}

	return 0;
}
