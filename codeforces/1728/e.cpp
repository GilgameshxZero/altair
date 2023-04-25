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

namespace Rain::Algorithm {
	// GCD using Euclidean algorithm.
	template <typename Integer>
	inline Integer greatestCommonDivisor(Integer x, Integer y) {
		while (x != 0) {
			std::tie(y, x) = std::make_pair(x, y % x);
		}
		return y;
	}

	// GCD using extended Euclidean algorithm gives Bezout's identity
	// coefficients.
	template <typename Integer>
	inline std::tuple<Integer, Integer, Integer> greatestCommonDivisorExtended(
		Integer x,
		Integer y) {
		Integer cX{0}, cY{1}, nX{1}, nY{0}, ratio;
		while (x != 0) {
			ratio = y / x;
			std::tie(y, x) = std::make_pair(x, y - ratio * x);
			std::tie(cX, nX) = std::make_pair(nX, cX - ratio * nX);
			std::tie(cY, nY) = std::make_pair(nY, cY - ratio * nY);
		}
		return {y, cX, cY};
	}

	// LCM.
	template <typename Integer>
	inline Integer leastCommonMultiple(Integer const &x, Integer const &y) {
		return x / greatestCommonDivisor(x, y) * y;
	}
}

using namespace Rain::Algorithm;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, M, S{0};
	cin >> N;

	vector<LL> D(N);
	RF(i, 0, N) {
		LL X, Y;
		cin >> X >> Y;
		S += X;
		D[i] = Y - X;
	}
	sort(D.begin(), D.end(), [](LL &X, LL &Y) { return X > Y; });
	LL LZ{0};
	for (; LZ < D.size(); LZ++) {
		if (D[LZ] < 0) {
			break;
		}
	}
	vector<LL> _P(N + 1);
	LL *P{_P.data() + 1};
	P[-1] = 0;
	RF(i, 0, N) {
		P[i] = P[i - 1] + D[i];
	}
	cin >> M;
	RF(i, 0, M) {
		LL X, Y;
		cin >> X >> Y;
		auto [G, cX, cY]{greatestCommonDivisorExtended(X, Y)};
		if (N % G != 0) {
			cout << "-1\n";
			continue;
		}
		cX *= N / G;
		cY *= N / G;
		auto L{leastCommonMultiple(X, Y)};
		LL R{(cY * Y % L + L) % L}, F{max(0LL, (LZ - R) / L)}, Z{-1};
		if (R + F * L - 1 < N) {
			Z = P[R + F * L - 1];
		}
		if (R + (F + 1) * L - 1 < N) {
			Z = max(Z, P[R + (F + 1) * L - 1]);
		}
		cout << (Z == -1 ? -1 : S + Z) << '\n';
	}

	return 0;
}
