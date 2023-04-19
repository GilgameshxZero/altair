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
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		multimap<LL, LL> C;
		RF(i, 0, N - 1) {
			if (A[i] > A[i + 1]) {
				C.insert({A[i] - A[i + 1], i + 1});
			}
		}
		vector<LL> ans;
		RF(i, 1, N + 1) {
			auto j{C.lower_bound(i + 1)};
			if (j == C.begin()) {
				ans.push_back(1);
			} else {
				j--;
				ans.push_back(j->second + 1);
				C.erase(j);
			}
		}
		RF(i, 0, N) {
			cout << ans[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
