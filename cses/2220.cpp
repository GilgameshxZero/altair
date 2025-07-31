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

LL solve(LL A) {
	if (A == 0) {
		return 1;
	}
	vector<LL> D;
	while (A > 0) {
		D.push_back(A % 10);
		A /= 10;
	}
	D.push_back(0);
	LL C{0};
	bool tops{true};
	RF(i, D.size() - 2, -1) {
		C = C * 9;
		if (i != D.size() - 2) {
			C += 9;
		}
		if (tops) {
			if (D[i] > D[i + 1]) {
				C += D[i] - 1;
			} else {
				C += D[i];
			}
		}
		if (D[i] == D[i + 1]) {
			tops = false;
		}
	}
	return C + tops + 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL A, B;
	cin >> A >> B;
	cout << solve(B) - (A == 0 ? 0 : solve(A - 1));
	return 0;
}
