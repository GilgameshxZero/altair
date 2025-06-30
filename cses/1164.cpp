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

	LL Z{0}, N;
	cin >> N;

	vector<pair<LL, pair<bool, LL>>> E;
	RF(i, 0, N) {
		LL a, b;
		cin >> a >> b;
		E.push_back({a, {false, i}});
		E.push_back({b, {true, i}});
	}
	sort(E.begin(), E.end());

	set<LL> R;
	vector<LL> S(N);
	RF(i, 0, E.size()) {
		if (E[i].second.first) {
			R.insert(S[E[i].second.second]);
		} else {
			if (R.empty()) {
				R.insert(Z++);
			}
			S[E[i].second.second] = *R.begin();
			R.erase(R.begin());
		}
	}

	cout << Z << '\n';
	RF(i, 0, N) {
		cout << S[i] + 1 << ' ';
	}

	return 0;
}
