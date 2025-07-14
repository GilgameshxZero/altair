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

	LL N, T;
	cin >> N >> T;
	unordered_map<LL, LL> Z;
	vector<LL> S(N);
	Z[0] = N;
	RF(i, 0, T) {
		LL A, B;
		cin >> A >> B;
		Z[S[A - 1]]--;
		if (Z[S[A - 1]] == 0) {
			Z.erase(S[A - 1]);
		}
		S[A - 1] += B;
		Z[S[A - 1]]++;
		cout << Z.size() << '\n';
	}

	return 0;
}
