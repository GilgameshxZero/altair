#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> P(N);
		RF(i, 0, N) {
			cin >> P[i];
		}
		P.push_back(LLONG_MAX);
		LL R[2]{0, P[1] - P[0]}, Z{0};
		RF(i, 1, N) {
			LL S[2]{0, min(P[i] - P[i - 1], P[i + 1] - P[i])};
			S[0] = max(S[0], P[i] - P[i - 1] - R[1]);
			S[1] = min(S[1], P[i] - P[i - 1] - R[0]);
			if (S[0] >= S[1]) {
				S[0] = 0;
				S[1] = min(P[i] - P[i - 1], P[i + 1] - P[i]);
				S[1] = min(S[1], P[i] - P[i - 1] - R[0]);
			} else {
				Z++;
			}
			swap(S, R);
		}
		cout << Z << '\n';
	}

	return 0;
}
