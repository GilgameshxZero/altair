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
		vector<pair<pair<LL, LL>, pair<LL, LL>>> P(N);
		vector<pair<pair<LL, LL>, pair<bool, bool>>> E;
		RF(i, 0, N) {
			cin >> P[i].first.first >> P[i].first.second >> P[i].second.first >>
				P[i].second.second;
			E.push_back({{P[i].first.first, i}, {false, false}});
			E.push_back({{P[i].first.second, i}, {false, true}});
			E.push_back({{P[i].second.first, i}, {true, false}});
			E.push_back({{P[i].second.second, i}, {true, true}});
		}
		sort(E.begin(), E.end());
		vector<pair<LL, LL>> Y;
		RF(i, E.size() - 1, -1) {
			if (E[i].second.first == false || E[i].second.second == false) {
				continue;
			}
			Y.push_back({P[E[i].first.second].first.first, E[i].first.first});
			for (; i >= 0 && E[i].first.first >= Y.back().first; i--) {
				if (E[i].second.first == true && E[i].second.second == true) {
					Y.back().first =
						min(Y.back().first, P[E[i].first.second].first.first);
				}
			}
			i++;
		}
		map<LL, LL> X;
		RF(i, 0, Y.size()) {
			X[Y[i].first] = Y[i].second;
		}
		LL Q;
		cin >> Q;
		RF(i, 0, Q) {
			LL x;
			cin >> x;
			auto j{X.upper_bound(x)};
			if (j == X.begin()) {
				cout << x << '\n';
				continue;
			}
			j--;
			if (j->second >= x) {
				cout << j->second << ' ';
			} else {
				cout << x << ' ';
			}
		}
		cout << '\n';
	}

	return 0;
}
