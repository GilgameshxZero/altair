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

array<LL, 5001> F;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> A(N), B(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		B[0] = 1;
		RF(i, 1, N) {
			B[i] = -LLONG_MAX / 2;
			if (A[i - 1] == A[i]) {
				B[i] = max(B[i], B[i - 1] + 1);
			}
			LL amax{0}, j;
			for (j = i - 3; j >= -1; j -= 2) {
				F[A[j + 1]]++;
				F[A[j + 2]]++;
				if (F[A[j + 1]] > F[amax]) {
					amax = A[j + 1];
				}
				if (F[A[j + 2]] > F[amax]) {
					amax = A[j + 2];
				}
				if ((j == -1 || A[j] == A[i]) && F[amax] <= (i - j - 1) / 2) {
					B[i] = max(B[i], (j == -1 ? 1LL : B[j] + 1));
				}
			}
			j += 2;
			for (; j <= i - 3; j += 2) {
				F[A[j + 1]]--;
				F[A[j + 2]]--;
			}
		}
		LL ans{0}, amax{0};
		RF(i, N - 1, -1) {
			if (F[amax] <= (N - 1 - i) / 2 && (N - 1 - i) % 2 == 0) {
				ans = max(ans, B[i]);
			}
			F[A[i]]++;
			if (F[A[i]] > F[amax]) {
				amax = A[i];
			}
		}
		RF(i, 0, N) {
			F[A[i]]--;
		}
		cout << ans << '\n';
	}

	return 0;
}
