#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

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

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

array<array<LL, (1LL << 17)>, 18> C, D;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N, Q;
		cin >> N >> Q;
		vector<pair<LL, LL>> LR(Q);
		RF(i, 0, Q) {
			cin >> LR[i].first >> LR[i].second;
			LR[i].first--;
			LR[i].second--;
		}
		sort(LR.begin(), LR.end());
		auto RL{LR};
		RF(i, 0, Q) {
			swap(RL[i].first, RL[i].second);
		}
		sort(RL.begin(), RL.end());
		LL LRI{0}, RLI{0}, CC{0}, DC{0};
		LL const MBC(mostSignificant1BitIdx(N) + 1);
		RF(i, 0, N) {
			for (; LRI < Q && LR[LRI].first <= i; LRI++) {
				CC++;
				RF(j, 0, MBC) {
					C[j][LR[LRI].first % (1LL << j)]++;
				}
			}
			for (; RLI < Q && RL[RLI].first < i; RLI++) {
				CC--;
				DC -= RL[RLI].first - RL[RLI].second + 1;
				RF(j, 0, MBC) {
					C[j][RL[RLI].second % (1LL << j)]--;
					D[j][RL[RLI].second % (1LL << j)] -=
						(RL[RLI].first - RL[RLI].second) / (1LL << j) +
						1;
				}
			}
			DC += CC;
			RF(j, 0, MBC) {
				D[j][i % (1LL << j)] += C[j][i % (1LL << j)];
			}
			LL Y{DC};
			RF(j, 1, MBC) {
				Y += D[j][(i + 1) % (1LL << j)] * (1LL << (j * 2 - 1));
			}
			// cout << '(';
			// RF(j, 1, C.size()) {
			// 	RF(k, 0, 1LL << j) {
			// 		cout << C[j][k] << ',';
			// 	}
			// 	cout << ';';
			// }
			// cout << ')';
			// cout << '(';
			// RF(j, 1, C.size()) {
			// 	RF(k, 0, 1LL << j) {
			// 		cout << D[j][k] << ',';
			// 	}
			// 	cout << ';';
			// }
			// cout << ')';
			cout << Y << ' ';
		}
		RF(i, 0, MBC) {
			RF(j, 0, 1LL << i) {
				C[i][j] = D[i][j] = 0;
			}
		}
		cout << '\n';
	}

	return 0;
}
