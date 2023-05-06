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

		vector<LL> B(N);
		RF(i, 0, N) {
			cin >> B[i];
		}
		set<pair<LL, LL>> C, A;
		A.insert({B[0], 0});
		A.insert({B[1] + 1, 1});
		C.insert({0, 0});
		C.insert({B[0] + B[1] - 1 + 1, 1});
		LL Z{0};
		RF(i, 2, N) {
			Z = max(
				Z,
				C.rbegin()->first - C.rbegin()->second + B[i] -
					(i - C.rbegin()->second));
			C.insert(
				{A.rbegin()->first - A.rbegin()->second + B[i] -
					 (i - A.rbegin()->second) + i,
				 i});
			A.insert({B[i] + i, i});
		}
		cout << Z << '\n';
	}

	return 0;
}
