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

array<LL, 100000> A;
array<LL, 100001> F;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, K;
	cin >> N >> K;
	RF(i, 0, N) {
		cin >> A[i];
	}

	F.fill(0);
	LL Fs{0}, pc{K - 3}, ans{0};
	for (LL i{0}; i < N; i += 2) {
		pc += 2;
		if (pc == N) {
			ans += Fs - F[A[i]];
			pc -= 2;
			while (Fs > 1) {
				Fs -= 2;
				F[A[i]]--;
				F[A[pc]]--;
				i += 2;
				pc -= 2;
				ans += Fs - F[A[i]];
			}
			break;
		} else if (pc == N + 1) {
			pc -= 2;
			Fs--;
			F[A[pc]]--;
			pc -= 2;
			while (Fs > 1) {
				Fs -= 2;
				F[A[i]]--;
				F[A[pc]]--;
				i += 2;
				pc -= 2;
				ans += Fs - F[A[i]];
			}
			break;
		} else {
			Fs++;
			F[A[pc]]++;
			if (i >= K - 1) {
				Fs--;
				F[A[i]]--;
			}
			ans += Fs - F[A[i]];
		}
	}

	F.fill(0);
	Fs = 0;
	pc = K - 2;
	for (LL i{1}; i < N; i += 2) {
		pc += 2;
		if (pc == N) {
			ans += Fs - F[A[i]];
			pc -= 2;
			while (Fs > 1) {
				Fs -= 2;
				F[A[i]]--;
				F[A[pc]]--;
				i += 2;
				pc -= 2;
				ans += Fs - F[A[i]];
			}
			break;
		} else if (pc == N + 1) {
			pc -= 2;
			Fs--;
			F[A[pc]]--;
			pc -= 2;
			while (Fs > 1) {
				Fs -= 2;
				F[A[i]]--;
				F[A[pc]]--;
				i += 2;
				pc -= 2;
				ans += Fs - F[A[i]];
			}
			break;
		} else {
			Fs++;
			F[A[pc]]++;
			if (i >= K) {
				Fs--;
				F[A[i]]--;
			}
			ans += Fs - F[A[i]];
		}
	}

	cout << ans;
	return 0;
}
