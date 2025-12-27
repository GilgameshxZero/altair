#include <random>
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

LL const C_C{1024};

mt19937 mt(
	std::chrono::duration_cast<std::chrono::nanoseconds>(
		std::chrono::high_resolution_clock::now()
			.time_since_epoch())
		.count());

bool verify(LL X, LL L, LL R, LL C) {
	normal_distribution<double> U(C, (R - L) / 8.0);
	RF(i, 0, C_C) {
		LL Y{(LL)U(mt)};
		if (Y < L || Y >= R) {
			continue;
		}
		if ((X ^ Y) < L || (X ^ Y) >= R) {
			return true;
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL _T;
	cin >> _T;
	while (_T--) {
		LL L, R;
		cin >> L >> R;
		if (L == R) {
			cout << "0\n";
			continue;
		}
		R++;
		LL Z{1};
		RF(i, 0, 55) {
			// cout << (1LL << (i + 1)) << ' '
			// 		 << (L % (1LL << (i + 1))) << ' '
			// 		 << (R % (1LL << (i + 1))) << '\n';
			if (
				L % (1LL << (i + 1)) == 0 &&
				R % (1LL << (i + 1)) == 0) {
				Z *= 2;
			} else if (
				L % (1LL << (i + 1)) == (1LL << i) &&
				R % (1LL << (i + 1)) == (1LL << i)) {
				LL X{L ^ (R - 1)};
				bool F{false};
				RF(j, 0, 50) {
					LL J{L + (1LL << j)};
					if (J >= R) {
						break;
					}
					if ((J ^ X) != R - (1LL << j) - 1) {
						F = true;
						break;
					}
				}
				if (!F) {
					Z *= 2;
				}
				break;
			}
		}
		cout << Z - 1 << '\n';
	}

	return 0;
}
