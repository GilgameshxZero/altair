#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
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

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		LL L(Rain::Algorithm::mostSignificant1BitIdx(N));
		vector<LL> R;
		vector<bool> V(N, true), W(N);
		RF(i, 0, N) {
			R.push_back(i + 1);
		}
		RF(i, 0, L + 1) {
			LL C1{0}, C0{0}, Q1{0}, Q0{0};
			RF(j, 0, R.size()) {
				if (R[j] & (1 << i)) {
					C1++;
				} else {
					C0++;
				}
			}
			RF(j, 0, N - 1) {
				if (V[j]) {
					if (Q1 == C1) {
						Q0++;
						W[j] = false;
						continue;
					} else if (Q0 == C0) {
						Q1++;
						W[j] = true;
						continue;
					}
					cout << "? " << j + 1 << ' ' << (1 << i) << endl;
					LL x;
					cin >> x;
					Q1 += x == 1;
					Q0 += x == 0;
					W[j] = x == 1;
				}
			}
			if (C1 == Q1) {
				vector<LL> RR;
				RF(j, 0, R.size()) {
					if (!(R[j] & (1 << i))) {
						RR.push_back(R[j]);
					}
				}
				swap(RR, R);
				RF(j, 0, N - 1) {
					if (V[j]) {
						if (W[j]) {
							V[j] = false;
						}
					}
				}
			} else {
				vector<LL> RR;
				RF(j, 0, R.size()) {
					if (R[j] & (1 << i)) {
						RR.push_back(R[j]);
					}
				}
				swap(RR, R);
				RF(j, 0, N - 1) {
					if (V[j]) {
						if (!W[j]) {
							V[j] = false;
						}
					}
				}
			}
		}
		cout << "! " << R[0] << endl;
	}

	return 0;
}
