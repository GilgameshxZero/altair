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
		vector<pair<LL, LL>> A(N);
		set<LL> zero, one;
		RF(i, 0, N) {
			cin >> A[i].first;
			A[i].second = i;
			zero.insert(i);
		}
		sort(A.begin(), A.end());

		LL Z{0};
		RF(i, N - 1, -1) {
			zero.erase(A[i].second);
			one.insert(A[i].second);

			LL b[3];
			b[1] = 
		}

		cout << Z << '\n';
	}

	return 0;
}
