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

	LL T;
	cin >> T;
	while (T--) {
		string S;
		cin >> S;

		vector<vector<LL>> ll;
		vector<pair<LL, LL>> mlp;
		mlp.push_back({LLONG_MIN, LLONG_MIN});
		LL l{0}, Z{0};
		RF(i, 0, S.length()) {
			if (ll.size() == l) {
				ll.push_back(vector<LL>());
			}
			ll[l].push_back(i);
			while (!mlp.empty() && mlp.back().first > -l) {
				mlp.pop_back();
			}
			mlp.push_back({-l, i});

			l += S[i] == '(' ? 1 : -1;
			LL p = lower_bound(
							 mlp.begin(),
							 mlp.end(),
							 pair<LL, LL>{-l * 2, 0}) -
				mlp.begin() - 1;
			p = mlp[p].second + 1;
			if (ll.size() == l) {
				ll.push_back(vector<LL>());
			}
			LL q = lower_bound(ll[l].begin(), ll[l].end(), p) -
				ll[l].begin();
			q = ll[l].size() - q;
			Z += q;
		}
		cout << Z << '\n';
	}

	return 0;
}
