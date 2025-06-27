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
 
	LL N, M;
	cin >> N >> M;
	vector<LL> F(N + 1), P(N + 1);
	P[0] = LLONG_MIN;
	RF(i, 0, N) {
		LL x;
		cin >> x;
		P[x] = i + 1;
		F[i + 1] = x;
	}
	LL Z{1};
	RF(i, 1, N + 1) {
		if (P[i] < P[i - 1]) {
			Z++;
		}
	}
	RF(i, 0, M) {
		LL x, y;
		cin >> x >> y;
		if (F[x] > F[y]) {
			swap(x, y);
		}
		Z -= P[F[x]] < P[F[x] - 1];
		Z -= P[F[x] + 1] < P[F[x]];
		if (F[x] + 1 != F[y]) {
			Z -= P[F[y]] < P[F[y] - 1];
		}
		Z -= P[F[y] + 1] < P[F[y]];
		swap(P[F[x]], P[F[y]]);
		swap(F[x], F[y]);
		Z += P[F[x]] < P[F[x] - 1];
		Z += P[F[x] + 1] < P[F[x]];
		Z += P[F[y]] < P[F[y] - 1];
		if (F[y] + 1 != F[x]) {
			Z += P[F[y] + 1] < P[F[y]];
		}
		cout << Z << '\n';
	}
	return 0;
}