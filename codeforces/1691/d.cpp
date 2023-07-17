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

namespace Rain::Algorithm {
	// Most significant 1-bit for unsigned integral types of at most long long in
	// size. Undefined result if x = 0.
	template <typename Integer>
	inline std::size_t mostSignificant1BitIdx(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_clzll)
		return 8 * sizeof(unsigned long long) - __builtin_clzll(x) - 1;
#endif
#endif
		for (std::size_t bit{8 * sizeof(Integer) - 1};
				 bit != std::numeric_limits<std::size_t>::max();
				 bit--) {
			if (x & (static_cast<Integer>(1) << bit)) {
				return bit;
			}
		}
		return std::numeric_limits<std::size_t>::max();
	}

	// Least significant 1-bit for unsigned integral types of at most long long in
	// size. Undefined result if x = 0.
	template <typename Integer>
	inline std::size_t leastSignificant1BitIdx(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_ctzll)
		return __builtin_ctzll(x);
#endif
#endif
		for (std::size_t bit{0}; bit != 8 * sizeof(Integer); bit++) {
			if (x & (static_cast<Integer>(1) << bit)) {
				return bit;
			}
		}
		return std::numeric_limits<std::size_t>::max();
	}

	// Count of 1-bits in unsigned integral types of at most long long in size.
	template <typename Integer>
	inline std::size_t bitPopcount(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_popcountll)
		return __builtin_popcountll(x);
#endif
#endif
		std::size_t count{0};
		for (std::size_t bit{0}; bit != 8 * sizeof(Integer); bit++) {
			count += !!(x & (static_cast<Integer>(1) << bit));
		}
		return count;
	}
}

using namespace Rain::Algorithm;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> A;
		A.push_back(0);
		map<LL, vector<LL>> P;
		RF(i, 0, N) {
			LL x;
			cin >> x;
			if (x <= 0) {
				A.back() += x;
			} else {
				P[x].push_back(A.size());
				A.push_back(x);
				A.push_back(0);
			}
		}

		vector<LL> B(A.size()), C(A.size());
		B[0] = A[0];
		RF(i, 1, A.size()) {
			B[i] = B[i - 1] + A[i];
		}
		C.back() = A.back();
		RF(i, A.size() - 2, -1) {
			C[i] = C[i + 1] + A[i];
		}
		vector<vector<LL>> D, E;
		LL msb(mostSignificant1BitIdx(A.size()));
		D.resize(msb + 1);
		D[0].resize(A.size());
		RF(i, 0, A.size()) {
			D[0][i] = B[i];
		}
		RF(i, 1, D.size()) {
			D[i].resize(A.size() + 1 - (1LL << i));
			RF(j, 0, D[i].size()) {
				D[i][j] = max(D[i - 1][j], D[i - 1][j + (1LL << (i - 1))]);
			}
		}
		E.resize(msb + 1);
		E[0].resize(A.size());
		RF(i, 0, A.size()) {
			E[0][i] = C[i];
		}
		RF(i, 1, E.size()) {
			E[i].resize(A.size() + 1 - (1LL << i));
			RF(j, 0, E[i].size()) {
				E[i][j] = max(E[i - 1][j], E[i - 1][j + (1LL << (i - 1))]);
			}
		}
		auto rangeMax{[](vector<vector<LL>> &X, LL x, LL y) {
			LL msb(mostSignificant1BitIdx(y - x + 1));
			return max(X[msb][x], X[msb][y + 1 - (1LL << msb)]);
		}};

		set<LL> L;
		L.insert(-1);
		L.insert(A.size());
		bool fail{false};
		for (auto i{P.rbegin()}; !fail && i != P.rend(); i++) {
			RF(j, 0, i->second.size()) {
				auto k{L.upper_bound(i->second[j])};
				LL low{*prev(k) + 1}, high{*k - 1};
				LL sum{
					A[i->second[j]] + rangeMax(E, low, i->second[j]) - C[i->second[j]] +
					rangeMax(D, i->second[j], high) - B[i->second[j]]};
				if (sum > i->first) {
					fail = true;
					break;
				}
			}
			RF(j, 0, i->second.size()) {
				L.insert(i->second[j]);
			}
		}
		cout << (fail ? "NO" : "YES") << '\n';
	}

	return 0;
}
