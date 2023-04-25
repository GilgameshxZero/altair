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
		multiset<LL> A, B;
		RF(i, 0, N) {
			LL X;
			cin >> X;
			A.insert(X);
		}
		RF(i, 0, N) {
			LL X;
			cin >> X;
			B.insert(X);
		}
		auto digLog{[](LL X) {
			LL T{10}, Z{1};
			while (true) {
				if (X < T) {
					return Z;
				}
				Z++;
				T *= 10;
			}
		}};
		LL Z{0};
		while (!A.empty()) {
			if (*A.rbegin() == *B.rbegin()) {
				A.erase(A.find(*A.rbegin()));
				B.erase(B.find(*B.rbegin()));
			} else if (*A.rbegin() > *B.rbegin()) {
				Z++;
				A.insert(digLog(*A.rbegin()));
				A.erase(A.find(*A.rbegin()));
			} else {
				Z++;
				B.insert(digLog(*B.rbegin()));
				B.erase(B.find(*B.rbegin()));
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
