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

array<LL, 200000> A;
array<LL, 200001> F;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, K;
	cin >> N >> K;
	RF(i, 0, N) {
		cin >> A[i];
	}

	LL Fs{0}, ans{0}, wlow{0}, whigh{0};
	for (LL i{0}; i < N; i += 2) {
		LL nlow, nhigh;
		nlow = (K - 1) / 2 + (K - 1) / 2 - i;
		nhigh = N - 1 - (K - 1) / 2 + N - 1 - (K - 1) / 2 - i;
		nlow = max(0LL, nlow);
		nhigh = min(N - 1, nhigh);
		nlow = max(i, nlow);
		nhigh = min(i + K - 1, nhigh);
		if (nlow > nhigh) {
			continue;
		}
		for (; wlow < nlow; wlow += 2) {
			F[A[wlow]]--;
			Fs--;
		}
		for (; wlow > nlow; wlow -= 2) {
			F[A[wlow - 2]]++;
			Fs++;
		}
		for (; whigh <= nhigh; whigh += 2) {
			F[A[whigh]]++;
			Fs++;
		}
		for (; whigh > nhigh + 2; whigh -= 2) {
			F[A[whigh - 2]]--;
			Fs--;
		}

		ans += Fs - F[A[i]];
	}

	F.fill(0);
	Fs = 0;
	wlow = whigh = 1;
	for (LL i{1}; i < N; i += 2) {
		LL nlow, nhigh;
		nlow = (K - 1) / 2 + (K - 1) / 2 - i;
		nhigh = N - 1 - (K - 1) / 2 + N - 1 - (K - 1) / 2 - i;
		nlow = max(0LL, nlow);
		nhigh = min(N - 1, nhigh);
		nlow = max(i, nlow);
		nhigh = min(i + K - 1, nhigh);
		if (nlow > nhigh) {
			continue;
		}
		for (; wlow < nlow; wlow += 2) {
			F[A[wlow]]--;
			Fs--;
		}
		for (; wlow > nlow; wlow -= 2) {
			F[A[wlow - 2]]++;
			Fs++;
		}
		for (; whigh <= nhigh; whigh += 2) {
			F[A[whigh]]++;
			Fs++;
		}
		for (; whigh > nhigh + 2; whigh -= 2) {
			F[A[whigh - 2]]--;
			Fs--;
		}

		ans += Fs - F[A[i]];
	}

	cout << ans;
	return 0;
}
