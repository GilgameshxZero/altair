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
		LL K;
		string S;
		cin >> K >> S;

		vector<LL> L, C(S.size());
		LL Z{0};
		RF(i, 0, S.size()) {
			if (S[i] == '(') {
				L.push_back(i);
			} else {
				LL dist{i - L.back() - 1};
				L.pop_back();
				C[i] = dist / 2;
				Z += C[i];
			}
		}

		sort(C.begin(), C.end());
		RF(i, 0, min(K, (LL)C.size())) {
			Z -= C[C.size() - 1 - i];
		}
		cout << Z << '\n';
	}

	return 0;
}
