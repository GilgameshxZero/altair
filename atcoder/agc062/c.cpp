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

	LL N, K;
	cin >> N >> K;
	vector<LL> A(N);
	RF(i, 0, N) {
		cin >> A[i];
	}
	sort(A.begin(), A.end());

	map<LL, LL> I;
	I[0] = 0;
	RF(i, 0, N) {
		auto j{I.end()};
		do {
			j--;
			I[j->first + A[i]] = max(I[j->first + A[i]], j->second + A[i]);
		} while (j != I.begin());

		j = I.begin();
		while (next(j) != I.end()) {
			if (j->second >= next(j)->first - 1) {
				j->second = max(j->second, next(j)->second);
				I.erase(next(j));
			} else {
				j++;
			}
		}

		while (I.size() > 100000) {
			I.erase(prev(I.end()));
		}
	}

	vector<LL> Z;
	LL C{0};
	while (Z.size() < K) {
		if (I.count(C)) {
			C = I[C] + 1;
		}
		Z.push_back(C++);
	}
	RF(i, 0, K) {
		cout << Z[i] << ' ';
	}
	return 0;
}
