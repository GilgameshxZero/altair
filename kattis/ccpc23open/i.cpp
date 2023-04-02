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

	LL P, V;
	cin >> P;
	unordered_map<string, string> s2p;
	map<string, LL> ans;
	RF(i, 0, P) {
		string planet, species;
		LL N;
		cin >> planet >> N;
		ans[planet] = 0;
		RF(j, 0, N) {
			cin >> species;
			s2p[species] = planet;
		}
	}
	cin >> V;
	RF(i, 0, V) {
		LL M;
		string species;
		cin >> M >> species;
		ans[s2p[species]] += M;
	}

	for (auto &i : ans) {
		cout << i.first << ' ' << i.second << '\n';
	}
	return 0;
}
