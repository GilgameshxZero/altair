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

	LL N, A, B;
	cin >> N >> A >> B;
	vector<LL> X(N);
	RF(i, 0, N) {
		cin >> X[i];
	}

	vector<LL> Y(N);
	multiset<LL> S;
	LL O{0}, Z{LLONG_MIN};
	RF(i, 0, N) {
		O += X[i];
		Y[i] = X[i] - O;
		if (i - A + 1 >= 0) {
			S.insert(Y[i - A + 1]);
		}
		if (i - B >= 0) {
			S.erase(S.find(Y[i - B]));
		}
		if (!S.empty()) {
			Z = max(Z, *S.rbegin() + O);
		}
	}
	cout << Z;

	return 0;
}
