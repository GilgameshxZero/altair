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

	LL N, Q;
	cin >> N >> Q;

	vector<LL> A(N), B[2];
	RF(i, 0, N) {
		cin >> A[i];
	}
	sort(A.begin(), A.end());
	B[0].resize(N);
	B[1].resize(N);
	RF(i, 0, N) {
		B[0][i] = A[i] - i;
	}
	B[1] = B[0];
	B[1].back() = A.back();

	LL S[2]{
		*min_element(B[0].begin(), B[0].end()),
		*min_element(B[1].begin(), B[1].end() - 1)},
		C[2]{0, 0};
	RF(i, 0, 2) {
		RF(j, 0, N) {
			C[i] += B[i][j] - S[i];
		}
	}
	C[1] -= B[1].back() - S[1];

	vector<LL> D{A};
	RF(i, 0, N) {
		D[i] -= i;
	}

	vector<LL> preD(N), postA(N);
	preD[0] = D[0];
	postA.back() = A.back();
	RF(i, 1, N) {
		preD[i] = min(preD[i - 1], D[i]);
	}
	RF(i, N - 2, -1) {
		postA[i] = min(postA[i + 1], A[i]);
	}
	postA.push_back(LLONG_MAX / 2);

	RF(i, 0, Q) {
		LL K;
		cin >> K;
		if (K <= N) {
			cout << min(preD[K - 1] + K, postA[K]) << ' ';
			continue;
		}

		LL X{max(0LL, (K - N + 1) / 2)}, R{K - X * 2}, Y{(N - R) % 2};
		LL burns, best;
		if (Y == 1) {
			if (S[Y] + K >= B[1].back()) {
				burns = C[1] + (N - 1) * (S[Y] + K - B[1].back());
				best = B[1].back();
			} else {
				burns = C[1] + B[1].back() - (S[Y] + K);
				best = S[Y] + K;
			}
		} else {
			burns = C[Y];
			best = S[Y] + K;
		}

		if (X <= burns) {
			cout << best << ' ';
		} else {
			cout << best - (X - burns + N - 1) / N << ' ';
		}
	}

	return 0;
}
