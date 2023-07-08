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

	LL N, K;
	cin >> N >> K;
	vector<pair<LL, LL>> A(N);
	LL Y{0};
	RF(i, 0, N) {
		cin >> A[i].first >> A[i].second;
		Y += A[i].second;
	}
	if (Y <= K) {
		cout << "1\n";
		return 0;
	}
	sort(A.begin(), A.end());
	RF(i, 0, N) {
		Y -= A[i].second;
		if (i != N - 1 && A[i].first == A[i + 1].first) {
			continue;
		}
		if (Y <= K) {
			cout << A[i].first + 1 << '\n';
			break;
		}
	}

	return 0;
}
