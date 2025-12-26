#include <bit>
#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

namespace Rain::Algorithm {
	// Most significant 1-bit for unsigned integral types of
	// at most long long in size. Undefined result if x = 0.
	template <typename Integer>
	inline std::size_t mostSignificant1BitIdx(
		Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_clzll)
		return 8 * sizeof(unsigned long long) -
			__builtin_clzll(x) - 1;
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

	// Least significant 1-bit for unsigned integral types of
	// at most long long in size. Undefined result if x = 0.
	template <typename Integer>
	inline std::size_t leastSignificant1BitIdx(
		Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_ctzll)
		return __builtin_ctzll(x);
#endif
#endif
		for (std::size_t bit{0}; bit != 8 * sizeof(Integer);
				 bit++) {
			if (x & (static_cast<Integer>(1) << bit)) {
				return bit;
			}
		}
		return std::numeric_limits<std::size_t>::max();
	}

	// Count of 1-bits in unsigned integral types of at most
	// long long in size.
	template <typename Integer>
	inline std::size_t bitPopcount(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_popcountll)
		return __builtin_popcountll(x);
#endif
#endif
		std::size_t count{0};
		for (std::size_t bit{0}; bit != 8 * sizeof(Integer);
				 bit++) {
			count += !!(x & (static_cast<Integer>(1) << bit));
		}
		return count;
	}
}

using namespace Rain::Algorithm;

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
		LL N, K;
		cin >> N >> K;
		if (K % 2 == 1) {
			RF(i, 0, K) {
				cout << N << ' ';
			}
			cout << '\n';
			continue;
		}
		LL MSB(mostSignificant1BitIdx(N)), PPC(bitPopcount(N));
		if (PPC == 1) {
			RF(i, 0, K - 2) {
				cout << N << ' ';
			}
			cout << N << " 0\n";
			continue;
		}
		vector<pair<LL, LL>> B0C;
		vector<vector<LL>> BG;
		RF(i, 0, 32) {
			if ((1LL << i) & N) {
				BG.push_back({i});
			} else {
				B0C.push_back({i, PPC - BG.size()});
				B0C.back().second -= B0C.back().second % 2;
			}
		}
		if (B0C.empty()) {
			RF(i, 0, K - 2) {
				cout << N << ' ';
			}
			cout << N << " 0\n";
			continue;
		}
		reverse(BG.begin(), BG.end());
		LL TBCM{min(K, B0C[0].second)};
		if (TBCM == 0) {
			RF(i, 0, K - 2) {
				cout << N << ' ';
			}
			cout << N << " 0\n";
			continue;
		}
		while (BG.size() > TBCM) {
			BG[0].push_back(BG.back()[0]);
			BG.pop_back();
		}
		RF(i, 0, TBCM) {
			// cout << '(';
			// RF(j, 0, BG[i].size()) {
			// 	cout << BG[i][j] << ',';
			// }
			// cout << ')';
			LL n{N};
			RF(j, 0, BG[i].size()) {
				n ^= 1LL << BG[i][j];
			}
			// cout << n << ',';
			RF(j, 0, B0C.size()) {
				if (i < B0C[j].second) {
					n ^= 1LL << B0C[j].first;
				}
			}
			cout << n << ' ';
		}
		RF(i, 0, K - TBCM) {
			cout << N << ' ';
		}
		cout << '\n';
	}

	return 0;
}
